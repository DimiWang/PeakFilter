#include "myfilter.h"
#include "math.h"
MyFilter::MyFilter(int32_t peak_thr,int32_t ref_count)
{
    reset();
    m_config.peak_thr = peak_thr;
    m_config.ref_count = ref_count;
}

void MyFilter::addRefValue(int32_t value){
    m_ref_cur = (m_ref_cur+1)%m_config.ref_count;
    m_ref_values[m_ref_cur] = value;
    if(++m_ref_cnt>m_config.ref_count)
            m_ref_cnt = m_config.ref_count;
}

void MyFilter::calcAverage(int32_t value){
    m_local_average += value;
    m_local_average /= 2;
}

void MyFilter::addValue(int32_t value)
{
    m_values[0] = m_values[1];
    m_values[1] = m_values[2];
    m_values[2] = value;
    int32_t m_peak_val = abs(curValue()*curValue() - lastValue()*nextValue());
    calcAverage(value);
    if(m_peak_val<this->m_config.peak_thr){
        addRefValue(curValue());
    }else{
        addRefValue(locAverage());
    }
}

void MyFilter::reset()
{
    m_ref_cur = 0;
    m_ref_cnt =0;
    m_values[0] =m_values[2] =m_values[1];
    for(int i=0;i<100;i++){
        m_ref_values[i] =0;
    }
}

int32_t MyFilter::refValue()
{
    int32_t sum=0;
    for(int i=0;i<m_ref_cnt;i++){
        sum += m_ref_values[i];
    }
    return sum/m_config.ref_count;
}

void MyFilter::operator <<(int32_t value)
{
    addValue(value);
}

int32_t MyFilter::average3()
{
    int32_t sum = m_values[0]+m_values[1]+m_values[2];
    return sum/3;
}

int32_t MyFilter::value(ValueType type)
{
    switch(type){
    case ValAverage3:
        return average3();
    break;
    case ValLocalAverage:
        return locAverage();
        break;
    case ValRef:
       return refValue();
        break;
    }
}
