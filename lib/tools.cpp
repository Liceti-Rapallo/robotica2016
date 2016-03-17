int nextPos(int &pos, int a[])
{
    pos++;
    if(pos==sizeof(a)/sizeof(int)) return 0;
    else return pos;
}

void shiftArray(float *a)
{
    for(int i = sizeof(a)/sizeof(float)-2; i >= 0; i--)
        a[i+1] = a[i];
}
