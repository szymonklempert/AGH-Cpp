#include <set>
#include <vector>
#include <iostream>
using namespace std;

class relation
{
    class pair
    {
    public:
        int x;
        int y;
        //        bool operator<(const pair&other)const;
        pair(int _x, int _y) : x(_x), y(_y) {}
    };

public:
    vector<pair> pairs;
    /*
     * czy zawiera parę (x,y)?
     */
    bool has_pair(int x, int y) const;
    /*
     * dodaje parę
     * para musi być unikalna (nie może pojawiac sie kilka razy)
     */
    void add(int x, int y);
    /*
     * zwraca dziedzine relacji (iksy)
     */
    set<int> get_domain() const;
    /*
     * zwraca przeciwdziedzine relacji (igreki)
     */
    set<int> get_range() const;

    /*
     * czy relacja jest zwrotna?
     */

    bool is_reflexive() const;
    /*
     * czy relacja jest symetryczna?
     */
    bool is_symmetric() const;
    /*
     * czy jest przechodnia
     */
    bool is_transitive() const;
    /*
     * czy jest relacją równowazności
     */
    bool is_equivalence() const;
    /*
     *  czy jest antysymetryczna
     *  https://en.wikipedia.org/wiki/Antisymmetric_relation
     */
    bool is_antisymmetric() const;
    /*
     * Czy jest relacją częściowego porządkująca
     * https://en.wikipedia.org/wiki/Partially_ordered_set#Formal_definition
     */
    bool is_partial_order() const;
    /*
     * czy jest spójna
     * https://en.wikipedia.org/wiki/Connex_relation
     */
    bool is_connex() const;
    /*
     * czy jest relacja całkowitego porządku
     * https://en.wikipedia.org/wiki/Total_order
     */
    bool is_total_order() const;
    /*
     * Zapisuje relację w formacie dot
     * https://graphviz.org/
     */
    void to_dot(std::ostream &os) const;
};

/*
 * czy zawiera parę (x,y)?
 */
bool relation::has_pair(int x, int y) const
{
    for (int i = 0; i != pairs.size(); i++)
    {
        if (pairs[i].x == x && pairs[i].y == y)
        {
            return true;
        }
    }
    return false;
}
/*
 * dodaje parę
 * para musi być unikalna (nie może pojawiac sie kilka razy)
 */
void relation::add(int x, int y)
{
    if (!has_pair(x, y))
    {
        pair p(x, y);
        pairs.push_back(p);
    }
}
/*
 * zwraca dziedzine relacji (iksy)
 */
set<int> relation::get_domain() const
{
    set<int> r;
    for (int i = 0; i != pairs.size(); i++)
    {
        r.insert(pairs[i].x);
    }
    return r;
}
/*
 * zwraca przeciwdziedzine relacji (igreki)
 */
set<int> relation::get_range() const
{
    set<int> r;
    for (int i = 0; i != pairs.size(); i++)
    {
        r.insert(pairs[i].y);
    }
    return r;
}

/*
 * czy relacja jest zwrotna?
 */

bool relation::is_reflexive() const
{
    set<int>::iterator itr;
    for (int i = 0; i != pairs.size(); i++)
    {
        if (!(has_pair(pairs[i].x, pairs[i].y)))
        {
            return false;
        }
    }
    return true;
}
/*
 * czy relacja jest symetryczna?
 */
bool relation::is_symmetric() const
{
    for (int i = 0; i != pairs.size(); i++)
    {
        if (!(has_pair(pairs[i].y, pairs[i].x)))
        {
            return false;
        }
    }
    return true;
}
/*
 * czy jest przechodnia
 */
bool relation::is_transitive() const
{
    bool f;
    for (int j = 0; j != pairs.size(); j++)
    {
        for (int i = 1; i != pairs.size(); i++)
        {
            if ((has_pair(pairs[i].y, pairs[j].x) && has_pair(pairs[i].x, pairs[i].y && has_pair(pairs[i].x, pairs[i].x))))
            {
                f = true;
            }
            else
            {
                f = false;
                return f;
            }
        }
    }

    return f;
}
/*
 * czy jest relacją równowazności
 */
bool relation::is_equivalence() const
{
    if (is_reflexive() && is_symmetric() && is_transitive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 *  czy jest antysymetryczna
 *  https://en.wikipedia.org/wiki/Antisymmetric_relation
 */
bool relation::is_antisymmetric() const
{

    for (int i = 0; i != pairs.size(); i++)
    {
        if (has_pair(pairs[i].y, pairs[i].x) && pairs[i].x != pairs[i].y)
        {
            return false;
        }
    }
    return true;
}
/*
 * Czy jest częściowo porządkująca
 * https://en.wikipedia.org/wiki/Partially_ordered_set#Formal_definition
 */
bool relation::is_partial_order() const
{
    if (is_reflexive() && is_antisymmetric() && is_transitive())
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
 * czy jest spójna
 * https://en.wikipedia.org/wiki/Connex_relation
 */
bool relation::is_connex() const
{
    // for(int i  = 0; i != pairs.size(); i++){
    //  if(has_pair())
    for (int i = 0; i != pairs.size(); i++)
    {

        for (int j = 0; j != pairs.size(); j++)
        {
            if (pairs[i].x != pairs[j].x && !has_pair(pairs[i].x, pairs[j].x) && !has_pair(pairs[j].x, pairs[i].x))
            {
                return false;
            }
        }
    }
    return true;
}
/*
 * czy jest relacja całkowitego porządku
 */
bool relation::is_total_order() const
{
    if (is_connex() && is_antisymmetric() && is_transitive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * C:\Program Files (x86)\Graphviz2.38\bin\dot" -Tpng  %1 -o %~n1.png
 */
void relation::to_dot(std::ostream &os) const
{
    os << "digraph g{\n";
    for (auto &e : pairs)
    {
        os << e.x << " -> " << e.y << ";" << endl;
    }
    os << "}\n";
}

// Testy

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void info(const relation &r)
{
    cout << "is_reflexive: " << r.is_reflexive() << endl;
    cout << "is_symmetric: " << r.is_symmetric() << endl;
    cout << "is_transitive: " << r.is_transitive() << endl;
    cout << "is_equivalence: " << r.is_equivalence() << endl;
    cout << "is_antisymmetric: " << r.is_antisymmetric() << endl;
    cout << "is_partial_order: " << r.is_partial_order() << endl;
    cout << "is_connex: " << r.is_connex() << endl;
    cout << "is_total_order: " << r.is_total_order() << endl;
}

void test_relation_1()
{
    relation r;
    int n = 50;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (x % 7 == y % 7)
                r.add(x, y);
        }
    }
    info(r);
}

void test_relation_2()
{
    relation r;
    int n = 50;
    for (int x = 0; x < n; x++)
    {
        for (int y = 1; y < n; y++)
        {
            if (x % y == 0)
                r.add(x, y);
        }
    }
    info(r);
}
void test_relation_3()
{
    relation r;
    int n = 50;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (x <= y)
                r.add(x, y);
        }
    }
    info(r);
}

void test_relation_4()
{
    relation r;
    int n = 20;
    for (int x = -n; x < n; x++)
    {
        for (int y = -n; y < n; y++)
        {
            if (x * x <= y * y)
                r.add(x, y);
        }
    }
    info(r);
}

void test_relation_5()
{
    relation r;
    int n = 2;
    for (int x = -n; x < n; x++)
    {
        for (int y = -n; y < n; y++)
        {
            if (x * x <= y * y)
                r.add(x, y);
        }
    }
    info(r);
    r.to_dot(cout);
}

void test_relation_6()
{
    relation r;
    int n = 5;
    for (int x = 0; x < n; x++)
        r.add(x, x);
    for (int x = 0; x < n - 3; x++)
    {
        for (int y = 1; y < n; y++)
        {
            if (x < y + 2)
                r.add(x, y);
        }
    }
    info(r);
    r.to_dot(cout);
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    cout << "test 1:" << endl;
    test_relation_1();
    cout << "test 2:" << endl;
    test_relation_2();
    cout << "test 3:" << endl;
    test_relation_3();
    cout << "test 4:" << endl;
    test_relation_4();
    cout << "test 5:" << endl;
    test_relation_5();
    cout << "test 6:" << endl;
    test_relation_6();
    return 0;
}
