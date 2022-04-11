#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  // 배열 사이즈 4로 정의

typedef char element;   //char형을 큐 element의 형으로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];   //MAX_QUEUE_SIZE 크기는 4
	int front, rear;                 //QUE에서 위치 지정 변수 front, rear 선언
}QueueType;  //QueueType 구조체 재정의


QueueType *createQueue();  
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();  


int main(void)
{
    printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);

	QueueType *cQ = createQueue();  //구조체 포인터 선언;
	element data;  

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //comand 값 입력

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //q또는 Q입력시 quit


	return 1;
}

QueueType *createQueue()  //공백큐 생성
{
	QueueType *cQ;  //구조체 포인터
	cQ = (QueueType *)malloc(sizeof(QueueType));  //포인터에 메모리 동적 할당으로 동적할당으로 원형 큐 이용
	cQ->front = 0;  //front 초기값 설정
	cQ->rear = 0;  // rear 초기값 설정
	return cQ;  //cQ값 반환
}

int freeQueue(QueueType *cQ)  //메모리 해제 함수
{
    if(cQ == NULL) return 1;  //null이라면 해제할 메모리가 없다.
    free(cQ);  //null이 아니라면 할당 해제
    return 1;  //반환
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);  // 요소값 입력
	return item;  //요소값 반환
}


int isEmpty(QueueType *cQ)  //큐가 비었나 확인하는 연산
{
	if (cQ->front == cQ->rear)  // front == rear은 큐의 공백을 확인하는 조건문
    {
		printf("Circular Queue is empty!");
		return 1;  
	}
 	else return 0;  //같지 않다면 0 리턴
}

int isFull(QueueType *cQ)  //큐가 찼나 확인하는 연산
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front)  //나머지 연산 필요하다.  rear+1/4의 나머지 == front 
    {
		printf(" Circular Queue is full!");  
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)  //rear에 enqueue하는 연산
{
	if(isFull(cQ)) return;  //프리컨디션 조사, 큐가 다 찼다면 enqueue를 하지 못해서
	else 
    {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)  //front에서 dequeue하는 연산
{
	if(isEmpty(cQ)) return;  //프리컨디션 조사, 큐가 비었다면 dequeue 할 필요가 없으니까 모순
	else 
    {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ) //que 출력 연산
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;  //first 인덱스값
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;  //rear 인덱스값

	printf("Circular Queue : [");

	i = first;
	while(i != last)  // first != last
    {
		printf("%3c", cQ->queue[i]);  //큐 요소 출력
		i = (i+1)%MAX_QUEUE_SIZE; 

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)  // 큐 디버깅 연산
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) 
        {
			printf("  [%d] = front\n", i); 
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);  

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


