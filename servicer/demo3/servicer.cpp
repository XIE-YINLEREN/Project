#include "service.h"

int sock_cids[SIZE]{};
int sock_index = 0;

int main()
{

	int Tcp_Message = socket(AF_INET, SOCK_STREAM, 0);
	int Tcp_File = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in IPV4_Message {};
	IPV4_Message.sin_family = AF_INET;
	IPV4_Message.sin_addr.s_addr = 0;		//ip��ַ
	IPV4_Message.sin_port = htons(PORT_MESSAGE);	//�˿ں�

	struct sockaddr_in IPV4_File {};
	IPV4_File.sin_family = AF_INET;
	IPV4_File.sin_addr.s_addr = 0;		//ip��ַ
	IPV4_File.sin_port = htons(PORT_FILE);	//�˿ں�


	if (bind(Tcp_Message, (struct sockaddr*)&IPV4_Message, sizeof(IPV4_Message)) < 0)
	{
		perror("bind");
		return -1;
	}

	if (bind(Tcp_File, (struct sockaddr*)&IPV4_File, sizeof(IPV4_File)) < 0)
	{
		perror("bind");
		return -1;
	}

	listen(Tcp_Message, 10);
	listen(Tcp_File, 10);

	printf("Servicer Opening\n");

	while (true)
	{
		if (fork() == 0) //��Ϣ����
		{
			while (true)
			{
				int cid = accept(Tcp_Message, NULL, NULL);
				if (cid > 0)
				{
					char buf[SIZE]{};
					sock_cids[sock_index] = cid;
					sock_index++;
					pthread_t pthread_DateBase;

					memset(buf, 0, SIZE);
					read(cid, buf, SIZE);//��ȡ�û��ź� ��������

					if (strcmp(buf, "DateBase") == 0)//�û���¼ע�Ṧ�� �ɹ�����ת����Ϣ�շ�
					{
						pthread_create(&pthread_DateBase, NULL, DateBase_Operate, &cid);
					}
				}
			}
		}
		else //�ļ�����
		{
			while (true)
			{
				int cid = accept(Tcp_File, NULL, NULL);
				if (cid > 0)
				{
					pthread_t pthread_file;
					pthread_create(&pthread_file, NULL, Pthread_File, &cid);
				}
			}
		}
		return -1;
	}

	}

	

/***************************************
������	��Message
����	��XIE
ά��ʱ�䣺2023/3/6
����	�����տͻ���<��Ϣ>����ת��<��Ϣ>���ͻ���
����	����int cid��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void Message(int cid) 
{
	char buf[SIZE]{};
	ssize_t len = 0;
	char flag[SIZE]{};

	printf("Message Function\n");

	while (1)
	{

		len = read(cid, buf, SIZE);
		if (len <= 0)//�ݴ���
		{
			break;
		}
		printf("%d:--%s\n", cid, buf);

		sprintf(flag, "%d:--%s\n", cid, buf);
		for (int i = 0; i < sock_index; i++)//Ⱥ����Ϣ
		{
			if (sock_cids[i] != cid)
			{
				write(sock_cids[i], flag, SIZE);
			}
		}
		memset(flag, 0, SIZE);
		memset(buf, 0, SIZE);
	}
	pthread_exit(NULL);
}


/***************************************
������	��Pthread_File
����	��XIE
ά��ʱ�䣺2023/3/6
����	���շ��ļ����������
����	����void* arg��
�������ͣ��������
�������ã����� Cid ���
***************************************/
void* Pthread_File(void* arg)
{
	int cid = *(int*)arg;

	while (true)
	{
		printf("File Function\n");

		char buf[SIZE]{};
		memset(buf, 0, SIZE);
		ssize_t flag = read(cid, buf, SIZE);

		if (flag <= 0)//�ݴ���
		{
			break;
		}
		if (strcmp(buf, "Recive Servicer File") == 0) //���ͷ������ļ����ͻ���
		{
			printf("SENT Servicer FILE\n");

			Dir_Service(cid); //�������ļ�Ŀ¼����
			File_Service(cid);//�������ļ�����

			pthread_exit(NULL);
		}
		if (strcmp(buf, "Recive Client File") == 0)//���Ϳͻ����ļ����ͻ���
		{
			printf("SENT Client FILE\n");
			Dir_Client(cid);//�ͻ����ļ�Ŀ¼����	
			File_Cilent(cid);//�ͻ����ļ�����

		}
		if (strcmp(buf, "File Sent") == 0)//���տͻ��˷������ļ�
		{
			printf("Recive  Client FILE\n");
			Recive_File(cid);
		}
		if (strcmp(buf, "Delete") == 0)//ɾ���ͻ����ļ�
		{
			printf("Delete  Client FILE\n");

			Dir_Client(cid);//�ͻ����ļ�Ŀ¼����
			Delete(cid); //ɾ���ͻ����ļ�

		}

	}


}

