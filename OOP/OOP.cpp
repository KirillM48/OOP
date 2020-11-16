#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <ctime>
using namespace std;
enum Suit { diamonds, clubs, hearts, spades };
enum Rank { one = 1, two, three, four, five, six, seven, eight, nine, ten, jack = 10, queen = 10, king = 10, ace = 11 };
class Card {
private:
    Suit m_suit;
    Rank m_rank;
    bool m_IsFaceUp;
public:
    Card(Rank r, Suit s) : m_suit(s), m_rank(r) { m_IsFaceUp = false; }
    ~Card() {}
    void Flip() { m_IsFaceUp = !m_IsFaceUp; }
    int GetValue() const { return static_cast<int>(m_rank); }
    friend ostream& operator<< (ostream& out, const Card& card);
};
class Hand {
protected:
    vector<Card*> m_Cards;
public:
    Hand() { m_Cards.reserve(7); }
    virtual ~Hand() { Clear(); }
    inline void Add(Card* pCard) { m_Cards.push_back(pCard); }
    void Clear() { 
        for (int i = 0; i < m_Cards.size(); ++i) delete m_Cards[i];
        m_Cards.clear();
    }
    int GetTotal() const {
        if (m_Cards.empty()) { return 0; }
        int total = 0;
        for (int i = 0; i < m_Cards.size() - 1; ++i) {
            total += m_Cards[i]->GetValue();
        }
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
            if ((*iter)->GetValue() == 11 && total >= 21)
            {
                total = total - 10;
            }
        }
        return total;
    }
};
class GenericPlayer : public Hand {
protected:
    string name;
public:
    GenericPlayer(string n): name(n) {}
    virtual ~GenericPlayer() {}
    virtual void isHitting() const = 0;
    bool isBoosted() { return (GetTotal() > 21); }
    void Bust() { if(isBoosted()) cout << name << " Перебор. " << GetTotal() << endl; }
    friend ostream& operator<< (ostream& out, const GenericPlayer& player);
};
class Player : public GenericPlayer {
public:
    Player(string n): GenericPlayer(n) {}
    virtual ~Player() {}
    bool IsHitting() const {
        int ans;
        cout << "Take card? (y/n): "; 
        cin >> ans;
        return (ans == 'y');
    }
    void Win() const { cout << name << " Win!" << endl; }
    void Lose() const { cout << name << " Lose!" << endl; }
    void Push() const { cout << name << " Pushes!" << endl; }
};
class House : public GenericPlayer {
public:
    House(string n): GenericPlayer(n) {}
    virtual ~House() {}
    bool IsHitting() const { return (GetTotal() <= 16); }
    void FlipFirstCard() {
        if (!(m_Cards.empty())) { m_Cards[0]->Flip(); }
        else { cout << "No card to flip!\n"; }
    }

};
class Deck :public Hand {
public:
    Deck() { m_Cards.reserve(52); Populate(); }
    ~Deck(){}
    void Populate(){
        for (int s = 0; s <= 3; ++s)
        {
            for (int r = 1; r <= 11; ++r)
            {
                Add(new Card(static_cast<Rank>(r), static_cast <Suit> (s)));
            }
        }
    }
    void Shuffle() { random_shuffle(begin(m_Cards), end(m_Cards)); }
    void Deal(Hand& aHand){
        if (!m_Cards.empty()) {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else { cout << "Out of cards. Unable to deal. "; }
    }
    void AdditionalCards(GenericPlayer& aPlayer){
        while (!(aPlayer.isBoosted()) && aPlayer.isBoosted())
        {
            Deal(aPlayer);
            cout << aPlayer << endl;
            if (aPlayer.isBoosted()) { aPlayer.Bust(); }
        }
    }
};
class Game {
private:
    Deck m_deck;
    House m_house;
    vector<Player> players;
public:
    Game(vector<string>& names) {
        for (const auto& a : names) { players.push_back(Player(a)); }
        srand(static_cast<unsigned int>(time(0)));
        m_deck.Populate();
        m_deck.Shuffle();
    }
    ~Game(){}
    void play() {
        for (int i = 0; i < 2; ++i) {
            for (auto& a : players) { m_deck.Deal(a); }
            m_deck.Deal(m_house);
        }
        m_house.FlipFirstCard();
        for (const auto& a : players) { cout << a << endl; }
        cout << m_house << endl;
        for (auto& a : players) { m_deck.AdditionalCards(a); }
        m_house.FlipFirstCard();
        cout << endl << m_house;
        m_deck.AdditionalCards(m_house);
        if (m_house.isBoosted()) { for (auto& a : players) { if (!a.isBoosted()) { a.Win(); } } }
        else {
            for (auto& a : players) {
                if (!a.isBoosted()) { a.Win(); }
                else if (a.GetTotal() < m_house.GetTotal()) { a.Lose(); }
                else { a.Push(); }
            }
        }
        for (auto& a : players) { a.Clear(); }
        m_house.Clear();
    }
};
ostream& operator<< (ostream& out, const Card& card) {
    const string RANKS[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9","10", "jack", "queen", "king", "ace" };
    const string SUITS[] = { "diamonds", "clubs", "hearts", "spades" };
    if (card.m_IsFaceUp) out << RANKS[card.m_rank] << " " << SUITS[card.m_suit];
    else out << "XX";
    return out;
}

ostream& operator<< (ostream& out, const GenericPlayer& player) {
    out << player.name << endl;
    for (int i = 0; i < player.m_Cards.size(); ++i) out << player.m_Cards[i] << " ";
    out << endl << "Points: " << player.GetTotal() << endl;
    return out;
}
vector<string> getPlNames()
{
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1-7):\n";
        cin >> numPlayers;
    }
    vector<string> names(numPlayers);
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> name;
        names.at(i) = name;
    }
    return names;
}
int main()
{
    cout << "\t\tWelcome to blackjack!\n\n";
    vector<string> names = getPlNames();
    cout << '\n';
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.play();
        cout << "\n Do you want to play again? (Y/N):\n";
        cin >> again;
    }
    return 0;
}