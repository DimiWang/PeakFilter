#ifndef MYFILTER_H
#define MYFILTER_H
#include "stdint.h"

class MyFilter
{
public:
    MyFilter(int32_t peak_thr,int32_t ref_count);
    void addValue(int32_t value);
    void reset();
    typedef enum{ValAverage3,ValLocalAverage,ValRef}ValueType;
    int32_t refValue() ;
    int32_t curValue() {return m_values[1];}
    int32_t nextValue() { return m_values[2];}
    int32_t lastValue() {return m_values[0];}
    int32_t locAverage() {return m_local_average;}
    int32_t average3() ;
    int32_t refCount() {return m_ref_cnt;}
    int32_t value(ValueType type);
    void operator << (int32_t value);

private:
    int32_t m_values[3];
    int32_t m_peak_val;
    int32_t m_local_average;
    int32_t m_ref_values[100];
    int32_t m_ref_cur;
    int32_t m_ref_cnt;

    struct {
        int32_t ref_count;
        int32_t peak_thr;
    }m_config;

    void addRefValue(int32_t value);
    void calcAverage(int32_t value);
};

#endif // MYFILTER_H
