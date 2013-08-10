#include "player.hpp"

// TODO: vielleicht besser mit Referenzen lösen...
Player::Player(const sf::Vector2f startingPosition, const Direction direction, const sf::Color color, const float maximumLength)
{
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

void Player::update(const sf::Time &time)
{
    // Größe, um die das letzte Teilstück erweitert werden soll
    float additionalSize = 64*time.asSeconds();

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
