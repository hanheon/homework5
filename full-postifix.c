#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10  //스택 사이즈 = 10 확정
#define MAX_EXPRESSION_SIZE 20  

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum // 연산자 우선순위 설정
{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;  //typedef문으로 precedence 구조체로 재정의 

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];
//크기가 define 배열 생성

int postfixStackTop = -1;  //stacktop = -1 초기화, 공백 조건
int evalStackTop = -1;  //stacktop = -1 초기화, 공백 조건

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();
//후위표기법 연상 알고리즘
int main()
{
    printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);

	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //q, Q 나오면 종료

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;  //x = 스택포인터
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)  //프리컨디션 조사, 공백이면 무의미
        return '\0';
    else   //공백이 아닐 때
    {
    	x = postfixStack[postfixStackTop--];  //위치 저장 변수 x에 pop한 뒤의 위치 저장
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;  //x = top을 가리키는 스택포인터
}

int evalPop()
{
    if(evalStackTop == -1)  //프리컨디션 조사, 공백이면 리턴 -1
        return -1;
    else
        return evalStack[evalStackTop--];  //pop한 배열 반환
}

/**
 * infix expression을 입력받는다.  //중위 표현 입력 받는다
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()  //후위로 변환하기 위해 중위 표현 식 입력받음
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)  //연산자 우선순위 구조체에서 symbol 매개로 하는 함수 사용
{
	switch(symbol) 
    {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) //c = 포인터
{
	if (postfixExp == '\0') //if postfixExp == null
		strncpy(postfixExp, c, 1);  //문자열 복사
	else
		strncat(postfixExp, c, 1);  // 문자열 붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)  // 읽은 문자 == 피연산자
		{
			x = *exp;
        	charCat(&x);  //charcat(char *c)에 x 주소값 전달
		}
        else if(getPriority(*exp) == lparen) 
        {

        	postfixPush(*exp);  //왼괄호면 postfix스택으로 전달
        }
        else if(getPriority(*exp) == rparen)  //오른괄호면
        {
        	while((x = postfixPop()) != '(') //이때 왼괄호가 아니라면
            {
        		charCat(&x);  //x를 postfixExp에 추가
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
            	x = postfixPop();  
            	charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
	}

    while(postfixStackTop != -1)  //스택탑이 공백이면
    {
    	x = postfixPop(); //pop한 문자를 x에 저장
    	charCat(&x);  //변수 x에 저장된 문자를 postfixExp에 추가
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()  //리셋 함수
{
	infixExp[0] = '\0';  //null값으로 리셋
	postfixExp[0] = '\0';  //null값으로 리셋

	for(int i = 0; i < MAX_STACK_SIZE; i++)  //10번 반복
		postfixStack[i] = '\0';  //모든 배열 요소에 null값으로 초기화
         
	postfixStackTop = -1;  //스택 공백 만들기
	evalStackTop = -1;  //스택 공백 만들기
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);  //length에 문자열 길이 저장
	char symbol;
	evalStackTop = -1;  //공백 조건

	for(i = 0; i < length; i++)   //postfixExp의 문자열 길이만큼 반복
	{ 
		symbol = postfixExp[i];
		if(getToken(symbol) == operand)   //getToken(symbol)이 피연산자라면
        {
			evalPush(symbol - '0'); 
		}
		else 
        {
			opr2 = evalPop();
			opr1 = evalPop();
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop();
}

