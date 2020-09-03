#ifndef _POS_
#define _POS_


struct position{
        float x=0;
        float y=0;
        float z=0;
        float w=1;
        bool on=0;
}req_pos;

void request_position(float x, float y, float z, float w){
	req_pos.x=x;
	req_pos.y=y;
	req_pos.z=z;
	req_pos.w=w;
	req_pos.on=1;
}

#endif

