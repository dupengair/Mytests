#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>

using std::string;


#define IN_FILE "/VMShare_Amb_fc15/nfs/Amb1/md_dump"
#define OUT_FILE "/VMShare_Amb_fc15/nfs/Amb1/md_dump_save.xml"


int main()
{
	FILE *fpr, *fpw;
	char buf[1024];
	int rnum = 0, wnum = 0;
	int cnt = 0;
	
	fpr = fopen(IN_FILE, "r");
	if(fpr != NULL)
		{
		printf("open %s success\n", IN_FILE);
		}
	else
		{
		perror("fopen in_file");
		printf("open %s failed\n", IN_FILE);
		goto exit;
		}
	
	fpw = fopen(OUT_FILE, "w");		
	if(fpw != NULL)
		{
		printf("open %s success\n", OUT_FILE);
		}
	else
		{
		perror("fopen out_file");
		printf("open %s failed\n", OUT_FILE);
		goto exit;
		}

	while(!feof(fpr))
		{
		memset(buf, 0, sizeof(buf));
		rnum = fread(buf, sizeof(buf), 1, fpr);
		
		if(rnum > 0)
			{			
			string s(buf);
			string save;
			string::size_type pos = 0;
			
			while((pos = s.find("<metadata", pos)) != string::npos)
				{				
				printf("%d ", pos);

				if(pos != 0)
					s.insert(pos, 1,  '\n');					

				pos+=5;
				cnt++;
				}
			
			printf("\n");	
			
			wnum = fwrite(s.c_str(), s.size()-17, 1, fpw);
			printf("write %d, size = %d\n", wnum, s.size());

			}		
		}

	printf("%d packets writed\n", cnt);

	
	
		

exit:
	if(fpr)
		{
		fclose(fpr);
		printf("%s closed\n", IN_FILE);
		}
	
	if(fpw)
		{
		fclose(fpw);
		printf("%s closed\n", OUT_FILE);
		}
	usleep(10);
}
	




