// #include "logic/bot.hpp"

// void Bot::missedShoot()
// {
//     std::vector<Position> empty_pos = playerBoard->getCells(Empty);
//     //player_board->shoot(empty_pos[rand() % empty_pos.size()]);
//     missedSteps--;
//     if (missedSteps == 0)
//         botState = RandomShoot;
// }

// void Bot::makeStep()
// {
//     switch (botState)
//     {
//     case MissedShoot:
//         missedShoot();
//         break;
//     case RandomShoot:
//         randomShoot();
//         break;
//     case FindDirection:
//         findDirection();
//         break;
//     case FishiningOff:
//         fishiningOff();
//         break;
//     default:
//         break;
//     }
// }