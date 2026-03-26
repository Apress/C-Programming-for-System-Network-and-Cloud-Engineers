#include <stdio.h>
struct BadOrg
{
    char d2;
    int d1;
    char d4;
    int d3;
    char d6;
    int d5;
}; 
struct GoodOrg 
{
    char d2;
    char d4;
    char d6;
    int d1;
    int d3;
    int d5;
}; 

struct DefAligned
{
   double d1;
   int i1;
   double d2;
   char c1
};

struct ForcedAligned
{
   double d1;
   int i1;
   double d2;
   char c1
}__attribute__((aligned(4)));

struct Packed
{
   double d1;
   int i1;
   double d2;
   char c1
}__attribute__((packed));

struct ForcedAlignedPacked
{
   double d1;
   int i1;
   double d2;
   char c1
}__attribute__((packed,aligned(8)));

struct SelectAligned1
{  
   double d1;
   int i1;
   double d2;
   char c1
}__attribute__((aligned(2)));

struct SelectAligned2
{
   double d1;
   int i1;
   double d2;
   char c1
}__attribute__((packed,aligned(4)));


int main()
{
    struct GoodOrg go;	
    struct BadOrg bo;	
    struct DefAligned a1;
    struct ForcedAligned a2;
    struct Packed p1;
    struct ForcedAlignedPacked pa2;
    struct SelectAligned1 a3;
    struct SelectAligned2 a4;
    printf("Good Organization = %lu\n", sizeof(go));
    printf("Bad Organization = %lu\n", sizeof(bo));
    printf("Default Organization = %lu\n", sizeof(a1));
    printf("Forced Organization = %lu\n", sizeof(a2));
    printf("Packed Organization = %lu\n", sizeof(p1));
    printf("Forced and packed Organization = %lu\n", sizeof(pa2));
    printf("Choose necessary alignment = %lu\n", sizeof(a3));
    printf("Choose necessary alignment = %lu\n", sizeof(a4));

    return 0;
}

