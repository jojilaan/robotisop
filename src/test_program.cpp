#include <test_program.hpp>
#include <darwin_connection.hpp>

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE 6

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr 314
#define __NR_sched_getattr 315
#endif

#ifdef __i386__
#define __NR_sched_setattr 351
#define __NR_sched_getattr 352
#endif

#ifdef __arm__
#define __NR_sched_setattr 380
#define __NR_sched_getattr 381
#endif

static volatile int done;

struct sched_attr
{
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid,
									const struct sched_attr *attr,
									unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
									struct sched_attr *attr,
									unsigned int size,
									unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

double getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0);
}

void sleepCustom(double msec)
{
	double start_time = getCurrentTime();
	double curr_time = start_time;

	do
	{
		usleep((start_time + msec) - curr_time);
		curr_time = getCurrentTime();
	} while (curr_time - start_time < msec);
}

void *run_deadline(void *data)
{
	struct sched_attr attr;
	int ret;
	unsigned int flags = 0;
	unsigned long long runtime = 1500000000L;
	unsigned long long period = 2500000000L;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = runtime;
	attr.sched_period = attr.sched_deadline = period;

	ret = sched_setattr(0, &attr, flags);
	if (ret < 0)
	{
		done = 0;
		perror("sched_setattr");
		exit(-1);
	}

	Connection connection = Connection("/dev/ttyUSB0");
	connection.openConnection();

	Packet packet = Packet(200, Packet::WRITE, 24, static_cast<unsigned char>(1));
	if (connection.transferPacket(packet))
	{
		std::cout << "SUCCES" << std::endl;
		packet = Packet(200, Packet::WRITEW, 26, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
			connection.transferPacket(packet);

		sleepCustom(300);
	}

	packet = Packet(1, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(3, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(5, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	packet = Packet(2, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(4, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(6, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	while (!done)
	{
		packet = Packet(2, Packet::WRITEW, 30, 400);
			connection.transferPacket(packet);

		usleep(1000000);

		packet = Packet(2, Packet::WRITEW, 30, 2000);
			connection.transferPacket(packet);

		sched_yield();
	}

	printf("deadline thread dies [%ld]\n", gettid());
	connection.closeConnection();
	return NULL;
}

int main()
{
	pthread_t thread;

	printf("main thread [%ld]\n", gettid());

	pthread_create(&thread, NULL, run_deadline, NULL);

	sleep(12);

	done = 1;
	pthread_join(thread, NULL);

	printf("main dies [%ld]\n", gettid());
	return 0;
}
