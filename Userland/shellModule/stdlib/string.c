int strcmp(char * s1, char * s2)
{
  while(*s1!=0 && *s2!=0)
  {
    if(*s1!=*s2) { return *s1-*s2; }
    s1++; s2++;
  }
  return *s1-*s2;
}

int strncmp(char * s1, char * s2, int n)
{
  while(*s1!=0 && *s2!=0 && n!=0)
  {
    if(*s1!=*s2) { return *s1-*s2; }
    s1++; s2++; n--;
  }
  return 0;
}
