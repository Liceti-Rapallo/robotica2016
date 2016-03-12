int nextPos(int &pos, int a[]){
    pos++;
    if(pos==sizeof(a)) return 0;
    else return pos;
}