#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
class ArrayInt {
private:
    int m_length;
    int* m_data;
public:
    ArrayInt() :m_length(0), m_data(nullptr) {}
    ArrayInt(int l) : m_length(l) {
        assert(l >= 0);
        if (l > 0)
        {
            m_data = new int[l];
            for (int i = 0; i < m_length; ++i) {
                m_data[i] = 0;
            }
        }
        else
            m_data = nullptr;
    }
    ~ArrayInt() { delete[] m_data; }
    void erase() {
        delete[]m_data;
        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }
    int& operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    int resize(int newLength) {
        if (newLength == m_length) return 0;
        if (newLength <= 0) { erase(); return 0; }
        int* data = new int[newLength];
        if (m_length > 0) {
            int elsementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int i = 0; i < elsementsToCopy; i++) { data[i] = m_data[i]; }
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }
    void insertBefore(int val, int idx) {
        assert(idx >= 0 && idx <= m_length);
        int* data = new int[m_length + 1];
        for (int i = 0; i < idx; ++i) {
            data[i] = m_data[i];
        }
        data[idx] = val;
        for (int i = idx; i < m_length; ++i) {
            data[i + 1] = m_data[i];
        }
        delete[] data;
        m_data = data;
        ++m_length;
    }
    void push_back(int val) { insertBefore(val, m_length); }
    void pop_back() {
        if (m_length <= 0) return;
        int* data = new int[m_length - 1];
        for (int i = 0; i < m_length - 1; ++i) {
            data[i] = m_data[i];
        }
        delete[] data;
        m_data = data;
        --m_length;
    }
    void pop_front() {
        if (m_length <= 0) return;
        int* data = new int[m_length - 1];
        for (int i = 1; i < m_length; ++i) {
            data[i] = m_data[i];
        }
        delete[] data;
        m_data = data;
        --m_length;
    }
    void sort(int first, int last)
    {
        int mid, count;
        int f = first;
        int l = last;
        mid = m_data[(f + l) / 2];
        do
        {
            while (m_data[f] < mid) ++f;
            while (m_data[l] > mid) --l;
            if (f <= l)
            {
                count = m_data[f];
                m_data[f] = m_data[l];
                m_data[l] = count;
                ++f;
                --l;
            }
        } while (f < l);
        if (first < l) sort(first, l);
        if (f < last) sort(f, last);
    }
    void print() {
        for (int i = 0; i < m_length; ++i) { cout << m_data[i] << " "; }
        cout << endl;
    }
};
//Задание 2
int uniq(vector<int>& v) {
    int count = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = i; j < v.size(); ++j) {
            if ((i != j) && (v[i] != v[j]))
            {
                ++count;
                break;
            }
        }
    }
    return count;
}
//BlackJack
enum class Suit { diamonds, clubs, hearts, peaks };
enum class Rank { one = 1, two, three, four, five, six, seven, eight, nine, ten, jack = 10, queen = 10, king = 10, ace = 11 };
class Card {
private:
    Suit m_suit;
    Rank m_rank;
    bool m_IsFaceUp;
public:
    Card() {}
    ~Card() {}
    void Flip() { m_IsFaceUp = !m_IsFaceUp; }
    int GetValue() { return static_cast<int>(m_rank); }
};
class Hand {
private:
    vector<Card*> m_Cards;
public:
    Hand() {}
    ~Hand() {}
    void Add(Card* pCard) { m_Cards.push_back(pCard); }
    void Clear() { m_Cards.clear(); }
    int GetTotal() {
        int total = 0;
        for (int i = 0; i < m_Cards.size() - 1; ++i) {
            total += m_Cards[i]->GetValue();
        }
        if (find(m_Cards.begin(), m_Cards.end(), Rank::ace) != m_Cards.end() && total >= 31)
            total = total - 10;
        return total;
    }
};
int main()
{
    const int size = 10;
    ArrayInt ar(size);
    for (int i = 0; i < ar.getLength(); ++i) { ar[i] = rand() % 100; }
    ar.print();
    ar.sort(0, size - 1);
    ar.print();
    vector<int> v(size);
    for (int i = 0; i < size - 1; ++i) { v[i] = rand() % 100; }
    cout << uniq(v);
}
