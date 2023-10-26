#ifndef BigInteger_h
#define BigInteger_h
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
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger p1,struct BigInteger p2);
struct BigInteger sub(struct BigInteger p1,struct BigInteger p2);
struct BigInteger mul(struct BigInteger p1,struct BigInteger p2);
struct BigInteger div1(struct BigInteger p1,struct BigInteger p2);
struct BigInteger mod(struct BigInteger p1,struct BigInteger p2);
void display(struct BigInteger ll);
#endif