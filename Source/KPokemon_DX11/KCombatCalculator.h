#pragma once
#include "KStd.h"
#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

//레벨에 따라 랜덤한 사이즈를 반환함
void leveltosize(int level, float& weight, float& height)
{
	//kg, m
	weight = randstep(0.1 * level, 0.9 * level);
	height = randstep(0.15, 2);
}

