#ifndef FILTER_H
#define FILTER_H


#define MASK_LENGTH 	(5)

class filter
{
public:
    filter();


    //moving average filter
    double movingAverageFilter();
    void insertIntoRawArray(double value);


    double raw_array[MASK_LENGTH] = {0,};
    int raw_array_index = 0;
    int counter=0;
};

#endif // FILTER_H
