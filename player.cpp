#include "player.hpp"

// TODO: vielleicht besser mit Referenzen lösen...
Player::Player(const sf::Vector2f startingPosition, const Direction direction, const sf::Color color, const float maximumLength)
{
    this->m_isActive = true;
    this->m_isAlive = true;
    this->m_maximumLength = maximumLength;
    sf::RectangleShape line;
    line.setFillColor(color);
    if(direction == Direction::Up || direction == Direction::Down)
    {
        line.setSize(sf::Vector2f(8, 8));
        line.setPosition(startingPosition - sf::Vector2f(4, 0)); // TODO: Rechnungen kontrollieren
    }
    else
    {
        line.setSize(sf::Vector2f(0, 8));
        line.setPosition(startingPosition - sf::Vector2f(0, 4)); // TODO: Rechnungen kontrollieren
    }
    this->m_lines.push_back(PlayerLineElement(line, direction));
}

void Player::changeDirection(const Direction direction)
{
    if(this->m_isAlive)
    {
        // neues Teilstück
        sf::RectangleShape newSegment;
        newSegment.setFillColor(this->m_lines.back().line.getFillColor());

        if(this->m_lines.back().getLength() <= 8)
        {
            switch(this->m_lines.back().direction)
            {
            case Direction::Up:
                if (direction == Direction::Up || direction == Direction::Down)
                    throw std::runtime_error("Direction can't be changed from 'Up' to 'Up' or 'Down'");

                newSegment.setSize(sf::Vector2f(this->m_lines.back().getLength(), 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.pop_back();
                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Down:
                if (direction == Direction::Up || direction == Direction::Down)
                    throw std::runtime_error("Direction can't be changed from 'Down' to 'Up' or 'Down'");

                // TODO: vielleicht andere, "genauere" Position des neuen Teiles nutzen
                newSegment.setSize(sf::Vector2f(this->m_lines.back().getLength(), 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.pop_back();
                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Left:
                if (direction == Direction::Left || direction == Direction::Right)
                    throw std::runtime_error("Direction can't be changed from 'Left' to 'Left' or 'Right'");

                newSegment.setSize(sf::Vector2f(8, this->m_lines.back().getLength()));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.pop_back();
                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Right:
                if (direction == Direction::Left || direction == Direction::Right)
                    throw std::runtime_error("Direction can't be changed from 'Right' to 'Left' or 'Right'");

                // TODO: vielleicht andere, "genauere" Position des neuen Teiles nutzen
                newSegment.setSize(sf::Vector2f(8, this->m_lines.back().getLength()));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.pop_back();
                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            }
        }
        else
        {
            switch(this->m_lines.back().direction)
            {
            case Direction::Up:
                if (direction == Direction::Up || direction == Direction::Down)
                    throw std::runtime_error("Direction can't be changed from 'Up' to 'Up' or 'Down'");

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() - sf::Vector2f(0, 8));
                this->m_lines.back().line.move(sf::Vector2f(0, 8));

                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Down:
                if (direction == Direction::Up || direction == Direction::Down)
                    throw std::runtime_error("Direction can't be changed from 'Down' to 'Up' or 'Down'");

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition() + this->m_lines.back().line.getSize() - sf::Vector2f(8, 8));

                this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() - sf::Vector2f(0, 8));

                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Left:
                if (direction == Direction::Left || direction == Direction::Right)
                    throw std::runtime_error("Direction can't be changed from 'Left' to 'Left' or 'Right'");

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition());

                this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() - sf::Vector2f(8, 0));
                this->m_lines.back().line.move(sf::Vector2f(8, 0));

                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Right:
                if (direction == Direction::Left || direction == Direction::Right)
                    throw std::runtime_error("Direction can't be changed from 'Right' to 'Left' or 'Right'");

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(this->m_lines.back().line.getPosition() + this->m_lines.back().line.getSize() - sf::Vector2f(8, 8));

                this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() - sf::Vector2f(8, 0));

                this->m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            }
        }
    }
}

Direction Player::getDirection()
{
    return this->m_lines.back().direction;
}

float Player::getLength()
{
    float length = 0.f;

    for(PlayerLineElement &e: this->m_lines)
    {
        length += e.getLength();
    }

    return length;
}

float Player::getMaximumLength()
{
    return this->m_maximumLength;
}

bool Player::isActive()
{
    return this->m_isActive;
}

bool Player::isAlive()
{
    return this->m_isAlive;
}

void Player::setLifeStatus(bool isAlive)
{
    this->m_isAlive = isAlive;
}

void Player::setMaximumLength(float maximumLength)
{
    this->m_maximumLength = maximumLength;
}

void Player::update(const sf::Time &time)
{
    if(this->m_isAlive)
    {
        // Größe, um die das letzte Teilstück erweitert werden soll
        float additionalSize = 0.5*time.asSeconds()*this->getLength();

        switch(this->m_lines.back().direction)
        {
        case Direction::Up:
            // Verändern der Größe
            this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() + sf::Vector2f(0, additionalSize));
            // Verändern der Position, damit das Teilstück nach oben erweitert wird
            this->m_lines.back().line.move(sf::Vector2f(0, (-1) * additionalSize));
            break;
        case Direction::Down:
            // Verändern der Größe
            this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() + sf::Vector2f(0, additionalSize));
            break;
        case Direction::Left:
            // Verändern der Größe
            this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() + sf::Vector2f(additionalSize, 0));
            // Verändern der Position, damit das Teilstück nach links erweitert wird
            this->m_lines.back().line.move(sf::Vector2f((-1) * additionalSize, 0));
            break;
        case Direction::Right:
            // Verändern der Größe
            this->m_lines.back().line.setSize(this->m_lines.back().line.getSize() + sf::Vector2f(additionalSize, 0));
            break;
        }
        // letztes Teilstück verkürzen, falls nötig
        this->adjustLength();
    }
    else
    {
        if(this->getLength() < this->m_maximumLength)
            this->m_maximumLength = this->getLength();
        this->m_maximumLength -= 1024*time.asSeconds();
        this->adjustLength();
        if(this->m_lines.empty())
            this->m_isActive = false;
    }
}

bool Player::firstElementIntersectsWithBoundaries()
{
    // Überprüfen, ob letztes Spielerelement mit den Wänden kollidiert ist
    if(this->m_lines.back().line.getPosition().x < 0 || this->m_lines.back().line.getPosition().y < 0 || (this->m_lines.back().line.getPosition().x + this->m_lines.back().line.getSize().x) > (64*16) || (this->m_lines.back().line.getPosition().y + this->m_lines.back().line.getSize().y) > (64*9))
        return true;
    else
        return false;
}

bool Player::firstElementIntersectsWithPlayer()
{
    // Überprüfen, ob letztes Spielerelement mit anderen Elementen kollidiert ist
    // kein Prüfen auf Kollision mit dem vorletzten Element, da durch Rundungsfehler fälschlicherweise Kollisionen erkannt werden würden (die jedoch real nicht möglich sind)
    for(int i = 0; i < (static_cast<int>(this->m_lines.size()) - 2); i++)
    {
        if(this->m_lines.back().line.getGlobalBounds().intersects(this->m_lines[i].line.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

bool Player::firstElementIntersectsWith(const sf::FloatRect &rect)
{
    return this->m_lines.back().line.getGlobalBounds().intersects(rect);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // TODO: mit for_each-Schleife o.ä. lösen
    for(unsigned int i = 0; i < this->m_lines.size(); i++)
    {
        target.draw(this->m_lines[i].line, states);
    }
}

void Player::adjustLength()
{
    // nichts tun, wenn keine Spielerelemente (mehr) vorhanden sind
    if(this->m_lines.empty())
        return;

    float difference = this->getLength() - this->m_maximumLength;
    // Spielerelement(e) verkürzen, wenn derzeitige Länge maximale Länge überschreitet
    if(difference > 0)
    {
        // Funktion rekursiv aufrufen, wenn das letzte Spielerelement kürzer als die zu korrigierende Differenz ist
        if(difference >= this->m_lines.front().getLength())
        {
            this->m_lines.erase(this->m_lines.begin());
            this->adjustLength();
            return;
        }
        else
        {
            switch(this->m_lines.front().direction)
            {
            case Direction::Up:
                // Verändern der Größe
                this->m_lines.front().line.setSize(this->m_lines.front().line.getSize() - sf::Vector2f(0, difference));
                break;
            case Direction::Down:
                // Verändern der Größe
                this->m_lines.front().line.setSize(this->m_lines.front().line.getSize() - sf::Vector2f(0, difference));
                // Verändern der Position, damit das Teilstück oben verkürzt wird
                this->m_lines.front().line.move(sf::Vector2f(0, difference));
                break;
            case Direction::Left:
                // Verändern der Größe
                this->m_lines.front().line.setSize(this->m_lines.front().line.getSize() - sf::Vector2f(difference, 0));
                break;
            case Direction::Right:
                // Verändern der Größe
                this->m_lines.front().line.setSize(this->m_lines.front().line.getSize() - sf::Vector2f(difference, 0));
                // Verändern der Position, damit das Teilstück links verkürzt wird
                this->m_lines.front().line.move(sf::Vector2f(difference, 0));
                break;
            }
        }
    }
}
