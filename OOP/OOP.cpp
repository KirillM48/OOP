#include<iostream>
#include<vector>
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
protected:
    vector<Card*> m_Cards;
public:
    Hand() {}
    virtual ~Hand() {}
    void Add(Card* pCard) { m_Cards.push_back(pCard); }
    void Clear() { m_Cards.clear(); }
    int GetTotal() {
        int total = 0;
        for (int i = 0; i < m_Cards.size() - 1; ++i) {
            total += m_Cards[i]->GetValue();
        }
        if (find(m_Cards.begin(), m_Cards.end(), Rank::ace) != m_Cards.end() && total >= 21)
            total = total - 10;
        return total;
    }
};
class GenericPlayer : public Hand {
private:
    string name;
public:
    GenericPlayer(string n) : name(n), Hand() {}
    ~GenericPlayer() {}
    void isHitting() { cout << "Take card?" << endl; }
    bool isBoosted() { (GetTotal() > 21) ? return 1 : return 0; }

};
int main{
    return;
}