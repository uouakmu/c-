#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// 노드 선언
typedef struct
{
	int item;
	struct StackNode* link;
} StackNode;

typedef struct
{
	StackNode* top;
} LinkedStackType;

// 스택 공백 검사용 함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

// 스택 초기화용 함수
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// 스택에 노드 삽입용 함수
void push(LinkedStackType* s, int item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)	// 메모리 할당이 되지 않았으면 에러 발생
	{
		fprintf(stderr, "메모리 할당 에러\n");
		return;
	}
	else	// 할당시 기존 노드와 연결
	{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}

// 스택의 마지막 값 반환 및 제거용 함수
int pop(LinkedStackType* s)
{
	if (is_empty(s))	// 노드가 비면 미실행
	{
		fprintf(stderr, "스택이 비어있음.\n");
		exit(1);
	}
	else	// 노드 존재시 최상위 노드를 불러 값을 반환 및 제거
	{
		StackNode* temp = s->top;
		int item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

// 스택 마지막 값을 확인, 반환하는 함수
int peek(LinkedStackType* s)
{
	if (is_empty(s))	// 노드가 비면 미실행
	{
		fprintf(stderr, "스택이 비어있음.\n");
		exit(1);
	}
	else	// 최상위 노드의 값을 리턴
	{
		return s->top->item;
	}
}


// 연산자의 우선순위 반환 함수
int prec(char op)
{
	switch (op)	// 각 우선순위에 따라 0, 1, 2로 반환
	{
	case '(': case ')':
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	}
	return -1;
}

// 중위표기 배열을 후위표기로 바꾸는 함수. 2번째 인자에 바꾼 식 저장
void infix_to_postfix(char exp[], char str[])
{
	int i = 0, k = 0;	// 여기서 k는 배열 위치에 관한 변수
	char ch, top_op;	// ch는 배열문자가 저장될 임시변수, top_op는 스택값이 저장될 임시변수
	int len = strlen(exp);	// 배열의 길이 저장 변수
	StackNode* s;

	init(&s);	// 스택 초기화
	for (i = 0; i < len; i++)
	{
		ch = exp[i];	// 입력받은 배열을 1칸씩 전진시키면서 문자 확인
		switch (ch)
		{
		case '+': case '-': case '*': case '/':	// 연산자
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				str[k++] = pop(&s);
			}
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);	// 왼쪽 괄호를 만날 때까지 출력
			while (top_op != '(')
			{
				str[k++] = top_op;
				top_op = pop(&s);
			}
			break;
		default:
			str[k++] = ch;
			break;
		}
	}
	while (!is_empty(&s))
	{
		str[k++] = pop(&s);
	}
}

// 후위표기식 연산 함수
int eval(char exp[])
{
	int op1, op2, value, i = 0;	// 여기서 op1,2 : 연산될 숫자를 pop 및 push 하는 변수
	char ch;
	StackNode* s;

	init(&s);	// 스택 초기화
	for (i = 0; exp[i] != '\0'; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
		{
			value = ch - '0';		// int형으로 변환
			push(&s, value);
		}
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+':
				push(&s, op1 + op2);
				break;
			case '-':
				push(&s, op1 - op2);
				break;
			case '*':
				push(&s, op1 * op2);
				break;
			case '/':
				push(&s, op1 / op2);
				break;
			}
		}
	}
	return pop(&s);
}


int main()
{
	char* data;	// 중위표기식 저장용 변수
	char str[100] = { '\0' };	// 바뀐 후위표기식을 저장할 배열
	int result;	// 연산값이 저장될 변수
	int i = 0;	// loop문 제어변수
	data = (char*)malloc(sizeof(char) * 100);	// 배열의 크기 할당
	printf("중위 표기식 입력 : ");
	gets(data);


	infix_to_postfix(data, str);	// 후위표기전환함수 호출

	printf("\n후위 표기식 출력 : %s\n", str);
	result = eval(str);	// 후위표기식 연산함수 호출
	printf("\n계산 결과 : %d\n", result);

	return 0;
}