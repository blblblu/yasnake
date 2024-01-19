#include "player.h"

Player::Player(const sf::Vector2f startingPosition, const Direction direction, const sf::Color color, const float maximumLength)
{
    m_isActive = true;
    m_isAlive = true;
    m_maximumLength = maximumLength;
    sf::RectangleShape line;
    line.setFillColor(color);
    if (direction == Direction::Up || direction == Direction::Down)
    {
        line.setSize(sf::Vector2f(8, 32));
        line.setPosition(startingPosition - sf::Vector2f(4, 0));
    }
    else
    {
        line.setSize(sf::Vector2f(32, 8));
        line.setPosition(startingPosition - sf::Vector2f(0, 4));
    }
    m_lines.push_back(PlayerLineElement(line, direction));
}

void Player::changeDirection(const Direction direction)
{
    if (m_isAlive)
    {
        sf::RectangleShape newSegment;
        newSegment.setFillColor(m_lines.back().line.getFillColor());

        if (m_lines.back().getLength() <= 8)
        {
            switch (m_lines.back().direction)
            {
            case Direction::Up:
                if (direction == Direction::Up || direction == Direction::Down)
                {
                    throw std::runtime_error("Direction can't be changed from 'Up' to 'Up' or 'Down'");
                }

                newSegment.setSize(sf::Vector2f(m_lines.back().getLength(), 8));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.pop_back();
                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Down:
                if (direction == Direction::Up || direction == Direction::Down)
                {
                    throw std::runtime_error("Direction can't be changed from 'Down' to 'Up' or 'Down'");
                }

                newSegment.setSize(sf::Vector2f(m_lines.back().getLength(), 8));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.pop_back();
                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Left:
                if (direction == Direction::Left || direction == Direction::Right)
                {
                    throw std::runtime_error("Direction can't be changed from 'Left' to 'Left' or 'Right'");
                }

                newSegment.setSize(sf::Vector2f(8, m_lines.back().getLength()));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.pop_back();
                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Right:
                if (direction == Direction::Left || direction == Direction::Right)
                {
                    throw std::runtime_error("Direction can't be changed from 'Right' to 'Left' or 'Right'");
                }

                newSegment.setSize(sf::Vector2f(8, m_lines.back().getLength()));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.pop_back();
                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            }
        }
        else
        {
            switch (m_lines.back().direction)
            {
            case Direction::Up:
                if (direction == Direction::Up || direction == Direction::Down)
                {
                    throw std::runtime_error("Direction can't be changed from 'Up' to 'Up' or 'Down'");
                }

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.back().line.setSize(m_lines.back().line.getSize() - sf::Vector2f(0, 8));
                m_lines.back().line.move(sf::Vector2f(0, 8));

                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Down:
                if (direction == Direction::Up || direction == Direction::Down)
                {
                    throw std::runtime_error("Direction can't be changed from 'Down' to 'Up' or 'Down'");
                }

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(m_lines.back().line.getPosition() + m_lines.back().line.getSize() - sf::Vector2f(8, 8));

                m_lines.back().line.setSize(m_lines.back().line.getSize() - sf::Vector2f(0, 8));

                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Left:
                if (direction == Direction::Left || direction == Direction::Right)
                {
                    throw std::runtime_error("Direction can't be changed from 'Left' to 'Left' or 'Right'");
                }

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(m_lines.back().line.getPosition());

                m_lines.back().line.setSize(m_lines.back().line.getSize() - sf::Vector2f(8, 0));
                m_lines.back().line.move(sf::Vector2f(8, 0));

                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            case Direction::Right:
                if (direction == Direction::Left || direction == Direction::Right)
                {
                    throw std::runtime_error("Direction can't be changed from 'Right' to 'Left' or 'Right'");
                }

                newSegment.setSize(sf::Vector2f(8, 8));
                newSegment.setPosition(m_lines.back().line.getPosition() + m_lines.back().line.getSize() - sf::Vector2f(8, 8));

                m_lines.back().line.setSize(m_lines.back().line.getSize() - sf::Vector2f(8, 0));

                m_lines.push_back(PlayerLineElement(newSegment, direction));
                break;
            }
        }
    }
}

Direction Player::getDirection()
{
    return m_lines.back().direction;
}

float Player::getLength()
{
    float length = 0.f;

    for (PlayerLineElement &e : m_lines)
    {
        length += e.getLength();
    }

    return length;
}

float Player::getMaximumLength()
{
    return m_maximumLength;
}

bool Player::isActive()
{
    return m_isActive;
}

bool Player::isAlive()
{
    return m_isAlive;
}

void Player::setLifeStatus(bool isAlive)
{
    m_isAlive = isAlive;
}

void Player::setMaximumLength(float maximumLength)
{
    m_maximumLength = maximumLength;
}

void Player::update(const sf::Time &time)
{
    if (m_isAlive)
    {
        float additionalSize = static_cast<float>(0.5 * time.asSeconds() * getLength());

        switch (m_lines.back().direction)
        {
        case Direction::Up:
            m_lines.back().line.setSize(m_lines.back().line.getSize() + sf::Vector2f(0, additionalSize));
            m_lines.back().line.move(sf::Vector2f(0, (-1) * additionalSize));
            break;
        case Direction::Down:
            m_lines.back().line.setSize(m_lines.back().line.getSize() + sf::Vector2f(0, additionalSize));
            break;
        case Direction::Left:
            m_lines.back().line.setSize(m_lines.back().line.getSize() + sf::Vector2f(additionalSize, 0));
            m_lines.back().line.move(sf::Vector2f((-1) * additionalSize, 0));
            break;
        case Direction::Right:
            m_lines.back().line.setSize(m_lines.back().line.getSize() + sf::Vector2f(additionalSize, 0));
            break;
        }
        adjustLength();
    }
    else
    {
        if (getLength() < m_maximumLength)
            m_maximumLength = getLength();
        m_maximumLength -= 1024 * time.asSeconds();
        adjustLength();
        if (m_lines.empty())
        {
            m_isActive = false;
        }
    }
}

bool Player::firstElementIntersectsWithBoundaries()
{
    if (m_lines.back().line.getPosition().x < 0 || m_lines.back().line.getPosition().y < 0 || (m_lines.back().line.getPosition().x + m_lines.back().line.getSize().x) > (64 * 16) || (m_lines.back().line.getPosition().y + m_lines.back().line.getSize().y) > (64 * 9))
        return true;
    else
        return false;
}

bool Player::firstElementIntersectsWithPlayer()
{
    for (int i = 0; i < (static_cast<int>(m_lines.size()) - 3); i++)
    {
        if (m_lines.back().line.getGlobalBounds().intersects(m_lines[i].line.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

bool Player::firstElementIntersectsWith(const sf::FloatRect &rect)
{
    return m_lines.back().line.getGlobalBounds().intersects(rect);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < m_lines.size(); i++)
    {
        target.draw(m_lines[i].line, states);
    }
}

void Player::adjustLength()
{
    if (m_lines.empty())
    {
        return;
    }

    float difference = getLength() - m_maximumLength;
    if (difference > 0)
    {
        if (difference >= m_lines.front().getLength())
        {
            m_lines.erase(m_lines.begin());
            adjustLength();
            return;
        }
        else
        {
            switch (m_lines.front().direction)
            {
            case Direction::Up:
                m_lines.front().line.setSize(m_lines.front().line.getSize() - sf::Vector2f(0, difference));
                break;
            case Direction::Down:
                m_lines.front().line.setSize(m_lines.front().line.getSize() - sf::Vector2f(0, difference));
                m_lines.front().line.move(sf::Vector2f(0, difference));
                break;
            case Direction::Left:
                m_lines.front().line.setSize(m_lines.front().line.getSize() - sf::Vector2f(difference, 0));
                break;
            case Direction::Right:
                m_lines.front().line.setSize(m_lines.front().line.getSize() - sf::Vector2f(difference, 0));
                m_lines.front().line.move(sf::Vector2f(difference, 0));
                break;
            }
        }
    }
}
