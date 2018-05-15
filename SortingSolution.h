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
    static String sort(const vector &arr, Mode mode);
};

#endif // SORTINGSOLUTION_H
