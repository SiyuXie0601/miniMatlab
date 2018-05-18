#ifndef SORTINGSOLUTION_H
#define SORTINGSOLUTION_H


class SortingSolution
{
public:
    enum Mode
        {
            Ascend, Descend//0为升序，1为降序
        };
    SortingSolution();
    static String sort(const vector &arr, Mode mode);//将arr中的数以mode方式排序，并将结果以字符串方式返回，元素与元素之间用逗号隔开(最后一个元素后无需,)，例如 "1,2,3,4"
};

#endif // SORTINGSOLUTION_H
