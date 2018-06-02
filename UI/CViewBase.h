//
// Created by matyas on 06/01/2018.
//

#ifndef SEM_CVIEWBASE_H
#define SEM_CVIEWBASE_H


/**
 * Abstract class that should be able to:
 * 1) Draw list of some items in some way.
 * 2) Pick one based on internal ID.
 * 3) Pagination within the list.
 */
template <typename _T>
class CViewBase
{
public:
    virtual ~CViewBase() = default;
    virtual void Update() = 0;
    virtual _T Find(int ID) const = 0;
    virtual void Previous() = 0;
    virtual void Next() = 0;
};

#endif //SEM_CVIEWBASE_H
