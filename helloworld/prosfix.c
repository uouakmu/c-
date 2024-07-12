#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// ��� ����
typedef struct
{
	int item;
	struct StackNode* link;
} StackNode;

typedef struct
{
	StackNode* top;
} LinkedStackType;

// ���� ���� �˻�� �Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

// ���� �ʱ�ȭ�� �Լ�
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// ���ÿ� ��� ���Կ� �Լ�
void push(LinkedStackType* s, int item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)	// �޸� �Ҵ��� ���� �ʾ����� ���� �߻�
	{
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		return;
	}
	else	// �Ҵ�� ���� ���� ����
	{
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}

// ������ ������ �� ��ȯ �� ���ſ� �Լ�
int pop(LinkedStackType* s)
{
	if (is_empty(s))	// ��尡 ��� �̽���
	{
		fprintf(stderr, "������ �������.\n");
		exit(1);
	}
	else	// ��� ����� �ֻ��� ��带 �ҷ� ���� ��ȯ �� ����
	{
		StackNode* temp = s->top;
		int item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

// ���� ������ ���� Ȯ��, ��ȯ�ϴ� �Լ�
int peek(LinkedStackType* s)
{
	if (is_empty(s))	// ��尡 ��� �̽���
	{
		fprintf(stderr, "������ �������.\n");
		exit(1);
	}
	else	// �ֻ��� ����� ���� ����
	{
		return s->top->item;
	}
}


// �������� �켱���� ��ȯ �Լ�
int prec(char op)
{
	switch (op)	// �� �켱������ ���� 0, 1, 2�� ��ȯ
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

// ����ǥ�� �迭�� ����ǥ��� �ٲٴ� �Լ�. 2��° ���ڿ� �ٲ� �� ����
void infix_to_postfix(char exp[], char str[])
{
	int i = 0, k = 0;	// ���⼭ k�� �迭 ��ġ�� ���� ����
	char ch, top_op;	// ch�� �迭���ڰ� ����� �ӽú���, top_op�� ���ð��� ����� �ӽú���
	int len = strlen(exp);	// �迭�� ���� ���� ����
	StackNode* s;

	init(&s);	// ���� �ʱ�ȭ
	for (i = 0; i < len; i++)
	{
		ch = exp[i];	// �Է¹��� �迭�� 1ĭ�� ������Ű�鼭 ���� Ȯ��
		switch (ch)
		{
		case '+': case '-': case '*': case '/':	// ������
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
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
			top_op = pop(&s);	// ���� ��ȣ�� ���� ������ ���
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

// ����ǥ��� ���� �Լ�
int eval(char exp[])
{
	int op1, op2, value, i = 0;	// ���⼭ op1,2 : ����� ���ڸ� pop �� push �ϴ� ����
	char ch;
	StackNode* s;

	init(&s);	// ���� �ʱ�ȭ
	for (i = 0; exp[i] != '\0'; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
		{
			value = ch - '0';		// int������ ��ȯ
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
	char* data;	// ����ǥ��� ����� ����
	char str[100] = { '\0' };	// �ٲ� ����ǥ����� ������ �迭
	int result;	// ���갪�� ����� ����
	int i = 0;	// loop�� �����
	data = (char*)malloc(sizeof(char) * 100);	// �迭�� ũ�� �Ҵ�
	printf("���� ǥ��� �Է� : ");
	gets(data);


	infix_to_postfix(data, str);	// ����ǥ����ȯ�Լ� ȣ��

	printf("\n���� ǥ��� ��� : %s\n", str);
	result = eval(str);	// ����ǥ��� �����Լ� ȣ��
	printf("\n��� ��� : %d\n", result);

	return 0;
}