#include<stdio.h>
#include<math.h>
#define resource 10000
#define sunlight 10
#define size 100
#define maxheight 9
#include <time.h>
#include <stdlib.h>

typedef struct grass {
	int x;
	int y;
//	float num;
//	float s;
//	int n;
	int generation;
	int height;
	int currentheight;
	int age;
	int shouming;
	int seed;
	int ancestor;
	struct grass* next;
}gra;
void grow(gra* a, int(*area)[size], int(* sun)[size])
{
	gra* head,* gra1,*gra2;
	int x1, y1,y2,z1,z2,flag=0,flag3=0, num=0; //零位不会死亡
	head = a;
	gra1 = a;
	gra2 = a;
	while (gra1 != NULL)
	{

		if (gra1->currentheight < gra1->height)
		{
			
			gra1->currentheight++;
			y1 = gra1->y - gra1->currentheight;
			y2 = gra1->y + gra1->currentheight;
			z1 = gra1->x - gra1->currentheight;
			z2 = gra1->x + gra1->currentheight;
			for (x1 = z1; x1 <= z2; x1++)
			{
		//		sun[x1][y1] -= 1;
		//		sun[x1][y2] -= 1;
		//		gra1->seed += sun[x1][y1]; /////seed shu meiyou gengxin
		//		gra1->seed += sun[x1][y2];
			}
			for (x1 = y1 + 1; x1 <= y2 - 1; x1++)
			{
		//		sun[z1][x1] -= 1;
		//		sun[z2][x1] -= 1;
		//		gra1->seed += sun[z1][x1];  /////warning!
		//		gra1->seed += sun[z2][x1];
			}
		}
		
		if (gra1->age == gra1->shouming)
		{
			area[gra1->x][gra1->y] = 100;
	//		for (x1 = gra1->x - gra1->height; x1 <= gra1->x + gra1->height; x1++)
	//			for (y1 = a->y - a->height; y1 <= a->y + a->height; y1++)
	//				sun[x1][y1]++;
			flag = 1;
			
	//		if (gra1 == gra2)
	//			flag = 2;
	//		gra1 = gra1->next;
	//		gra2->next = gra1;
	//		gra2 = gra1;
	//		continue;
		}
		if (gra1->age < gra1->shouming)
		{
	//		printf("%d %d %d\n", gra1->x, gra1->y, gra1->age);
			gra1->age++;
		}
		if (flag == 0)
		{
			gra2 = gra1;
			gra1 = gra1->next;
		}
		if (flag == 1)
		{
		  gra1 = gra1->next;
		  gra2->next = gra1;
		  flag = 0;
		}
		
		
	}
}
void multiple(gra* a, int(*area)[size], int(*seed)[size],int(*sun)[size])
{
	int x1, y1,z1,z2;
	srand(time(NULL));
	gra* head = a;
	while (head != NULL)
	{
	//	printf("%d\n", head->height);
		if (head->ancestor < 2)
		{
			if (head->ancestor == 1)
				head->ancestor = 2;
			for (x1 = 0; x1 < head->seed; x1++)
			{
				z1 = head->x - 1;
				//	printf("%d \n", rand() % (3));
				z1 += rand() % (3);
				z2 = head->y - 1;
				z2 += rand() % (3);
				if (head->height != 0)
				{
					z1 = rand() % (3 + 2 * head->height);
					z1 += (head->x - head->height - 1); //播种范围
					z2 = rand() % (3 + 2 * head->height);
					z2 += (head->y - head->height - 1);
				}


				//		srand(time(NULL));
				//		z2 = rand() % (4 * a->height);
				//		z2 += (a->y - 2 * a->height);
					//	if (z1 != z2)
					//	{

					//		exit(1); //////////////////// warning
					//	}
				//     if(head->height==9)
				//		printf("%d,, %d\n", z1,z2);
				if (z1 < 100 && z2<100 && z1 >= 0 && z2 >= 0 && area[z1][z2] == 100 && seed[z1][z2] > head->height) //种子生长条件
				//	if (area[z1][z2] == 100 )
				{
					//		printf("%d  %d\n", z1, z2);
					seed[z1][z2] = head->height;
					
				}

			}
		}
		head = head->next;
	}
}

void result(int(* area)[size], int(* seed)[size], gra* a, int(*sun)[size], int gener)
{
	int x, y,z1,z2;
	gra* a1 = a, *a2 =a;
	for(x=0;x<size;x++)
		for (y = 0; y < size; y++)
		{   
			//printf("%d  \n", seed[x][y]);
			if (seed[x][y] <= maxheight)
			{
			//	printf("%d  \n", seed[x][y]);
				gra* newgra = (gra*)malloc(sizeof(gra));
				newgra->height = seed[x][y];
				newgra->age = 0;

//				srand(time(NULL));
				z1 = rand() % (2);
			//	srand(time(NULL));
				z2 = rand() % (16);
			//	printf("pppp %d %d\n ", z2,z1);
				if (z2 == 0)
				{
					newgra->height += z1;
			//		newgra->shouming = newgra->height + z2%3;
				}
				if (z2 == 1)
				{
					newgra->height -= z1;
			//		newgra->shouming = newgra->height - z2%3;
				}
				newgra->shouming = newgra->height + 2;
			//	printf("%d\n", newgra->shouming);
				newgra->currentheight = 0;
				newgra->seed = newgra->height+2; 
				newgra->ancestor = 0;
				if (newgra->height == 0)
					newgra->seed = 4;   // number of seed!
				newgra->x = x;
				newgra->y = y;
				newgra->generation = gener;
				if (newgra->shouming > 0 && newgra->height <= maxheight && newgra->height >=0)
				{
					a1 = a1->next;
					a2->next = newgra;
					newgra->next = a1;
					a1 = a;
				//	printf("------------- %d --------------")
					area[x][y] = newgra->height;
					if (area[x][y] < 0 || area[x][y]>10)
					{
						printf("\nerror\n");
						exit(1);
					}
					sun[x][y]--;
				}
				seed[x][y] = maxheight+1;
				
			}
		}

}
int main(void)
{
	gra* head = NULL, *gra1 = NULL, *gra2 = NULL;
	FILE* fp = fopen("D:/grass_report1.txt", "w+");
	FILE* fp1 = fopen("D:/grass_report2.txt", "w+");
	FILE* fp2 = fopen("D:/grass_report3.txt", "w+");
	int x = 0, y = 0,z=0;
	char output[100] = {'\0'};
	char output2[100] = { '\0' };
	char output3[100] = { '\0' };
	output[0] = 'x';
	output[1] = ':';
//	output2[0] = '';
	srand(time(NULL));
	int area[size][size] = {0};
	int sun[size][size] = { sunlight };
	int seed[size][size] = { maxheight+1 };
	for(x=0;x<size;x++)
		for (y = 0; y < size; y++)
		{
			seed[x][y]= maxheight + 1;
			sun[x][y] =  sunlight ;
			area[x][y] = 100;
		}

	float size1 = 10000;
	gra1 = (gra*)malloc(sizeof(gra));
	gra1->age = 0;
	gra1->currentheight = 0;
	gra1->height = 0;
	gra1->age =0;
	gra1->generation = 0;
	gra1->shouming = 2;
	gra1->x = size / 2;
	gra1->y = size / 2;
	gra1->seed = sun[gra1->x][gra1->y];
	gra1->ancestor = 1;
	//printf("%d\n", gra1->seed);
	sun[gra1->x][gra1->y]--;
	gra1->next = NULL;
	head = gra1;
	gra2 = gra1;
	for (x = 0; x < 100; x++)
	{
	  printf("\n%d 世代\n", x);
	  grow(head, area, sun);
	  printf("grow 完成\n");
	  multiple(head, area, seed, sun);
	  printf("播种 完成\n");
	//  printf("ooo");
	  result(area, seed, head, sun,x);
	  printf("繁殖 完成\n");
	  fprintf(fp1, "No.%d\n",x);
	  for (y = 0; y < size; y++)
	  {
		  for (z = 0; z < size; z++)
		  {
			  fprintf(fp2, "%d ",sun[y][z]);
			  if (area[y][z] == 100)
				  fprintf(fp1,"*  ");
			  
			  else {
				  fprintf(fp1,"%d  ",area[y][z]);
			  }
			  
		  }
		  fprintf(fp1,"\n");
		  fprintf(fp2, "\n ");
	  }
	  fprintf(fp1, "\n");
	  fprintf(fp2, "\n");
	  while (gra2 != NULL)
	  {
		//  printf("%d and ", gra2->height);
		 

		  fprintf(fp,"No.%d x: %d  y: %d  height:  %d  age: %d  shouming: %d  gener: %d seed: %d\n",x, gra2->x, gra2->y, gra2->height,gra2->age,gra2->shouming,gra2->generation,gra2->seed);
		  
		  gra2 = gra2->next;
	  }
	  gra2 = head;
	  
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	
	return 0;
}