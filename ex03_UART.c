#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

int main()
{
	struct termios options, oldoptions;  // ���崮�����Խṹ�����������options�����������ô������ԣ�oldoptions����ԭ���ã����ڻָ���ԭ��������
	int fd;
	fd = open("/dev/s3c2410_serial1", O_RDWR);     // �򿪴���1
	tcgetattr(fd, &oldoptions);			// ��õ�ǰ�Ĵ���������Ϣ
	tcgetattr(fd, &options);
	cfsetispeed(&options, B115200);			// �������벨����Ϊ115200
	cfsetospeed(&options, B115200);			// �������������Ϊ115200

	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~PARENB;			// ���ô�������Ϊ������λΪ8λ��ֹͣλΪ1λ������żУ��
	options.c_cflag &= ~CSTOPB;

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);		// ���ô���ΪRawģʽ
	options.c_oflag &= ~OPOST;

	tcsetattr(fd, TCSANOW, &options);		// ������������Ч

	while(1)
	{
    	char buf[1024];
    	int len = 1024;
    	int rdadByte;
		rdadByte = read(fd, buf, len);		// ������
		if(buf[0] == '1')			        // ���������ַ�Ϊ��1����ظ����ڵ�ԭ���ò��˳�����
		{
			printf("\n");
			tcsetattr(fd, TCSANOW, &oldoptions);
			break;
		}
		unsigned int i = 0;
		for(i = 0; i < 0xfffff; i++);
		write(fd, buf, rdadByte);	        // д����
		write(fd, buf, rdadByte);	        // д����
	}
}
