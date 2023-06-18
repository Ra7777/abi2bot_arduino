#ifndef ABI2BOT_ARDUINO_WHEEL_HPP
#define ABI2BOT_ARDUINO_WHEEL_HPP

#include <string>
#include <cmath>


class Wheel
{
    public:

    std::string steer_name = "";
    std::string trac_name = "";
    double enc = 0;
    double steer_cmd = 0;
    double trac_cmd = 0;
    double steer_pos = 0;
    double steer_vel = 0;
    double trac_pos = 0;
    double trac_vel = 0;
    double vel = 0;
    double rads_per_count = 0;

    Wheel() = default;

    Wheel(const std::string &wheel_name1, const std::string &wheel_name2, int counts_per_rev)
    {
      setup(wheel_name1, wheel_name2, counts_per_rev);
    }

    
    void setup(const std::string &wheel_name1, const std::string &wheel_name2, int counts_per_rev)
    {
      steer_name = wheel_name1;
      trac_name = wheel_name2;
      rads_per_count = (2*M_PI)/counts_per_rev;
    }

    double calc_enc_angle()
    {
      return enc * rads_per_count;
    }



};


#endif // ABI2BOT_ARDUINO_WHEEL_HPP
