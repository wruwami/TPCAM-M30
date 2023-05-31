#include "filter.h"

filter::filter()
{

}

/* Mask 크기만큼 데이터를 평균낸다. */
double filter::movingAverageFilter()
{
    int i = 0;
    double sum = 0;

    for (i = 0; i < MASK_LENGTH; i++) {
        sum += raw_array[i];
    }
    if(counter<5){
        return sum/counter;
    }
    return ((double)sum / MASK_LENGTH);
}

/* 새로운 데이터를 array에 넣는다. */
void filter::insertIntoRawArray(double value)
{
    raw_array[raw_array_index] = value;
    if(counter<5){
        counter++;
    }

    raw_array_index++;

    if (raw_array_index >= MASK_LENGTH) {
        raw_array_index = 0;
    }
}
