#include<iostream>
#include<vector>
#include<string>
using namespace std;
enum class Suit { diamonds, clubs, hearts, peaks };
enum class Rank { one = 1, two, three, four, five, six, seven, eight, nine, ten, jack = 10, queen = 10, king = 10, ace = 11 };
template<class Type>
string getEnum(Type temp) {
    switch (temp)
        case Suit::diamonds: return "diamonds"; break;
        case Suit::clubs: return "clubs"; break;
        case Suit::hearts: return "hearts"; break;
        case Suit::peaks: return "peaks"; break;
        case Rank::one: return "one"; break;
        case Rank::two: return "two"; break;
        case Rank::three: return "three"; break;
        case Rank::four: return "four"; break;
        case Rank::five: return "five"; break;
        case Rank::six: return "six"; break;
        case Rank::seven: return "seven"; break;
        case Rank::eight: return "eight"; break;
        case Rank::nine: return "nine"; break;
        case Rank::ten: return "ten"; break;
        case Rank::jack: return "jack"; break;
        case Rank::queen: return "queen"; break;
        case Rank::king: return "king"; break;
        case Rank::ace: return "ace"; break;
}
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
    friend ostream& operator<< (ostream& out, const Card& card) {}
};
class Hand {
protected:
    vector<Card*> m_Cards;
public:
    Hand() {}
    virtual ~Hand() {}
    static void Add(Card* pCard) { m_Cards.push_back(pCard); }
    void Clear() { 
        for (int i = 0; i < m_Cards.size(); ++i) delete m_Cards[i];
        m_Cards.clear();
    }
    int GetTotal() const {
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
protected:
    string name;
public:
    GenericPlayer(string n) : name(n), Hand() {}
    ~GenericPlayer() {}
    static void isHitting() { cout << "Take card? Enter y or n." << endl; }
    bool isBoosted() { return (GetTotal() > 21); }
    void Bust() { if(isBoosted()) cout << name << " Перебор. " << GetTotal() << endl; }
    friend ostream& operator<< (ostream& out, const GenericPlayer& player) {}
};
class Player : public GenericPlayer {
public:
    Player(string n): GenericPlayer(n) {}
    ~Player(){}
    virtual bool IsHitting() const {
        int ans;
        do { isHitting(); cin >> ans; } while (ans != 'y' || ans != 'n');
        return (ans == 'y');
    }
    void Win() const { cout << name << " Win!" << endl; }
    void Lose() const { cout << name << " Lose!" << endl; }
    void Push() const { cout << name << " Draw!" << endl; }
};
class House : public GenericPlayer {
public:
    virtual bool IsHitting() const { return (GetTotal() <= 16); }
    void FlipFirstCard() { m_Cards[0]->Flip(); cout << m_Cards[0]; }

};
template<class Type>
ostream& operator<< (ostream& out, const Card& card) {
    if (card.m_IsFaceUp) return out << getEnum(card.m_rank) << " " << getEnum(card.m_suit);
    else return out << "XX";
}
template<class Type>
ostream& operator<< (ostream& out, const GenericPlayer& player) {
    out << player.name << endl;
    for (int i = 0; i < player.m_Cards.size(); ++i) out << player.m_Cards[i] << " ";
    out << endl << "Points: " << player.GetTotal() << endl;
    return out;
}
