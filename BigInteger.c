#include<stdio.h>
#include<stdlib.h>
struct node
{
    struct node*next;
    int data;
};
struct BigInteger
{
  struct node *head;
  int  length;
  int sign;
};
void ins_begin(struct node** head,int val);
struct BigInteger initialize(char *s)
{
  int i=0;
  struct BigInteger ll;
  ll.head=NULL;
  if(*s=='-')
  {
    ll.sign=-1;
    i++;
  }
  else
  ll.sign=1;
  while(*(s+i)!='\0')
  {
    ins_begin(&ll.head,s[i]-'0');
    i++;
  }
  if(ll.sign==-1)
  ll.length=i-1;
  else
  ll.length=i;
  return ll;
}
struct node * create(int n)
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  if (!temp)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }
  temp->data = n;
  temp->next = NULL;
  return temp;
}
void ins_begin(struct node** head,int val)//function to insert at the start of the list
{
   struct node *temp=create(val);
	temp->next=*head;
	*head=temp;
}
void dis(struct node *head)
{
  if (!head)
    return;

  dis(head->next);
  printf("%d", head->data);
}
void display(struct BigInteger ll)
{
 if(ll.sign==-1)
 {
  printf("-");
 }
 dis(ll.head);
}
struct node *rev(struct node *head)
{
  struct node *reversed = NULL;
   
  while (head != NULL)
  {
    struct node *newNode = create(head->data);
    newNode->next = reversed;
    reversed = newNode;
    head = head->next;
  }
  return reversed;
}
int compare(struct BigInteger pl, struct BigInteger ql) 
{
  int i;
 /*if(ql.sign>pl.sign)
  return 1;
  else if(pl.sign>ql.sign) 
  return 0;
  else*/
  {
  if (ql.length > pl.length)
  {
    return 1;
  }
  else if (pl.length == ql.length)
  {
    i = 0;
    struct node *m1 = rev(pl.head);
    struct node *m2 = rev(ql.head);
    while (i != pl.length && m1->data == m2->data)
    {
      i++;
      m1 = m1->next;
      m2 = m2->next;
    }

    if (i == pl.length || m2->data > m1->data)
    {
        free(m1);
        free(m2);
      return 1;
    } 
  }
  return 0;
  }
}
struct BigInteger add(struct BigInteger pl,struct BigInteger ql)
{
  struct BigInteger res;
  res.head=NULL;
  res.length=0;
  struct node *itr=NULL,*ptr=pl.head,*qtr=ql.head;
  int sum=0, carry = 0;
  long long int final=0;
  if(compare(pl,ql))
  {
   res.sign=ql.sign;
  }
  else
  res.sign=pl.sign;
  while (ptr || qtr || carry)
  {
    sum = (ptr ? (ptr->data)*pl.sign : 0) + (qtr ? (qtr->data)*ql.sign : 0) + carry;
    carry = sum / 10;
    /*if(sum<0)
    {
     sum=10+sum;
     carry--;
    }*/
    struct node *temp = create(sum % 10);
      temp->next=itr;
      itr = temp;
    res.length++;
    if (ptr)
      ptr = ptr->next;
    if (qtr)
     qtr = qtr->next;
  }
  while(itr!=NULL)
	{
		final=final*10+itr->data;
    struct node *temp = itr;
    itr = itr->next;
    free(temp); 
	}
  if(final==0)
  return initialize("0");
  if(final<0)
  final*=-1;
   while(final!=0)
   {
    struct node *temp=create(final%10);
     if (!res.head)
    {
       res.head = temp;
       itr = res.head;
    }
    else
    {
      itr->next = temp;
      itr = itr->next;
    }
    final=final/10;
   }
  return res;
}
struct BigInteger sub(struct BigInteger pl,struct BigInteger ql)
{
  struct BigInteger res;
  ql.sign*=-1;
  res=add(pl,ql);
  ql.sign*=-1;
  return res;
}
void multiplyByDigit(struct node *start, struct node *p1, int d)
{
  struct node *curr = start;
  struct node *back = NULL;
  int carry = 0;

  while (p1 || carry)
  {
    if (!curr)
    {
      curr = create(0);
      back->next = curr;
    }

    int prod = curr->data + (p1 ? p1->data : 0) * d + carry;
    curr->data = prod % 10;
    carry = prod / 10;

    if (p1)
    {
      p1 = p1->next;
    }

    back = curr;
    curr = curr->next;
  }
}

// Function to multiply two numbers represented by linked lists
struct BigInteger mul(struct BigInteger pl, struct BigInteger ql)
{
  struct BigInteger res;
  res.head=NULL;
  struct node *itr = NULL,*ptr=pl.head,*qtr=ql.head;
   int c=0;
  if (!pl.head||!ql.head)
  {
    return res;
  }
  while (qtr)
  {
    if (!res.head)
    {
      res.head = create(0);
      multiplyByDigit(res.head, ptr, qtr->data);
      itr = res.head;
    }
    else
    {
      multiplyByDigit(itr->next, ptr, qtr->data);
      itr = itr->next;
    }
    qtr = qtr->next;
  }
   itr=res.head;
    while(itr)
    {
      if(itr->data!=0)
      {
        c=1;
        break;
      }
      itr=itr->next;
    }
  res.sign=pl.sign*ql.sign;
  if(c==0)
  return initialize("0");
  return res;
}
struct BigInteger div1(struct BigInteger pl,struct BigInteger ql)
{
 
  int f=0,s=0;
  long long int c=0;
  struct BigInteger res,pp,ad=initialize("1");
  struct node *itr=NULL;
  res.head=NULL;
   if(!ql.head)
  {
    printf("cannot divide");
    return res;
  }
 if(ql.sign==-1)
  {
    ql.sign*=-1;
    f=1;
  }
  if(pl.sign==-1)
  {
    pl.sign*=-1;
    s=1;
  }
  pp=pl;
  while(pp.head&&compare(ql,pp))
  {
    pp=sub(pp,ql);
    c++;
  }
    if(c==0)
    return initialize("0");
  while(c!=0)
   {
    struct node *temp=create(c%10);
     if (!res.head)
    {
       res.head = temp;
       itr = res.head;
    }
    else
    {
      itr->next = temp;
      itr = itr->next;
    }
    c=c/10;
   }
  if(f==1)
  {
    ql.sign*=-1;
  }
  if(s==1)
  {
    pl.sign*=-1;
  }
  res.sign=pl.sign;
  return res;
}
struct BigInteger mod(struct BigInteger pl,struct BigInteger ql)
{
 
  int f=0,s=0;
  struct BigInteger pp;
   if(!ql.head)
  {
    printf("cannot divide");
    return pp;
  }
 if(ql.sign==-1)
  {
    ql.sign*=-1;
    f=1;
  }
  if(pl.sign==-1)
  {
    pl.sign*=-1;
    s=1;
  }
  pp=pl;
  while(pp.head&&compare(ql,pp))
  {
    pp=sub(pp,ql);
  }
    if(compare(pp,initialize("0") ))
  return initialize("0");
  if(f==1)
  {
    ql.sign*=-1;
  }
  if(s==1)
  {
    pl.sign*=-1;
  }
  pp.sign=pl.sign;
  return pp;
}
