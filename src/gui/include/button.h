#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <utils.h>
#include <widget.h>
#include <graphlib.h>
#include <text.h>
#include <interfaces.h>
#include <math.h>
#include <pictures.h>

#include <chrono>
using clockmy = std::chrono::high_resolution_clock;
using duration = std::chrono::duration<float, std::milli>;

constexpr auto AnimationTime = std::chrono::nanoseconds(std::chrono::seconds(1)).count() * 0.3;

//*************************************************************

template <typename Handler>
struct ButtonPictureRectangle: virtual public Widget, public IClickable<Handler>,
                               public ITestableRectangle, public IDrawablePicture {
    ButtonPictureRectangle(Handler handler, const MLPicture& picture, const Vector2i& size, const Vector2i& pos, const Color& bg) :
        Widget(size, pos, nullptr),
        IClickable<Handler>(handler),
        IDrawablePicture(picture), ITestableRectangle(),
        bg(bg)
    {}

    Color bg;
};
                    
//*************************************************************

template <typename Handler>
struct ButtonAnimColor: virtual public Widget, public IClickable<Handler>,
                        public ITestableCircle, public IHoverable {
    ButtonAnimColor(Handler handler, const MLPicture& mainPicture, const Color& sideColor,
                     int radius, const Vector2i& pos) :
        Widget(Vector2i(2 * radius, 2 * radius), pos, nullptr),
        IClickable<Handler>(handler),
        ITestableCircle(radius),
        sideColor(sideColor),
        mainPicture(mainPicture, Vector2i(sqrt(2) * radius, sqrt(2) * radius), Vector2i(0, 0)),
        isAnimated(false)
    {
        isHover = false;
    }

    void draw(MLTexture& texture, const Vector2i& absPos) override {
        MLSprite button(*PictureManager::getInstance()->getPicture(DefaultPictures::Picture::Button), size, absPos);
        button.draw(texture);

        if (isHover) {
            if (!isAnimated) {
                isAnimated = true;
                timeAnimated = clockmy::now();
            }
            else {
                MLCircle circle(absPos, radius, sideColor);

                double delta = (clockmy::now() - timeAnimated).count();
                if (delta > AnimationTime * 0.7) {
                    circle.setColor(Color(sideColor.x * 255, sideColor.y * 255, sideColor.z * 255, 0.7 * 255));
                    circle.draw(texture);
                } else {
                    auto currOpacity = delta / AnimationTime;
                    auto currColor = circle.getColor();
                    currColor.t = currOpacity;
                    circle.setColor(currColor);
                    circle.draw(texture);
                }
            }
        } else {
            if (isAnimated) {
                isAnimated = false;
                timeAnimated = clockmy::now();
                MLCircle circle(absPos, radius, Color(sideColor.x * 255, sideColor.y * 255, sideColor.z * 255, 0.7 * 255));
                circle.draw(texture);
            } else {
                double delta = (clockmy::now() - timeAnimated).count();
                if (delta < AnimationTime) {
                    auto currOpacity = delta / AnimationTime;
                    currOpacity = 0.7 - currOpacity;
                    if (currOpacity < 0) {
                        currOpacity = 0;
                    }
                    MLCircle circle(absPos, radius, Color(sideColor.x * 255, sideColor.y * 255, sideColor.z * 255, currOpacity * 255));
                    circle.draw(texture);
                }
            }
        }

        mainPicture.setPosition(absPos + Vector2i(int(radius * (1 - 1/sqrt(2))),int(radius * (1 - 1/sqrt(2))) ) );
        mainPicture.draw(texture);
    }

    MLSprite mainPicture;
    Color sideColor;
    bool isAnimated;
    clockmy::time_point timeAnimated;
};

//*************************************************************

template <typename Handler>
struct ButtonAnimPicture: virtual public Widget, public IClickable<Handler>,
                          public ITestableRectangle, public IHoverable {
    ButtonAnimPicture(Handler handler, const MLPicture& mainPicture, DefaultPictures::Picture sidePicture,
                     const Vector2i& size, const Vector2i& pos) :
        Widget(size, pos, nullptr),
        IClickable<Handler>(handler),
        ITestableRectangle(),
        mainPicture(mainPicture, size, Vector2i(0, 0)),
        sidePicture(sidePicture),
        isAnimated(false)
    {
        isHover = false;
    }

    void draw(MLTexture& texture, const Vector2i& absPos) override {
        mainPicture.setPosition(absPos);
        mainPicture.draw(texture);

        if (isHover) {
            if (!isAnimated) {
                isAnimated = true;
                timeAnimated = clockmy::now();
            }
            else {
                MLSprite sprite(*PictureManager::getInstance()->getPicture(sidePicture), size, absPos);

                double delta = (clockmy::now() - timeAnimated).count();
                if (delta > AnimationTime) {
                    sprite.draw(texture);
                } else {
                    auto currOpacity = delta / AnimationTime;
                    sprite.setColor(Color(255, 255, 255, 255 * currOpacity));
                    sprite.draw(texture);
                }
            }
        }
         else {
            if (isAnimated) {
                isAnimated = false;
                timeAnimated = clockmy::now();
                MLSprite sprite(*PictureManager::getInstance()->getPicture(sidePicture), size, absPos);
                sprite.draw(texture);
            } else {
                double delta = (clockmy::now() - timeAnimated).count();
                if (delta < AnimationTime) {
                    auto currOpacity = delta / AnimationTime;
                    currOpacity = 1 - currOpacity;
                    MLSprite sprite(*PictureManager::getInstance()->getPicture(sidePicture), size, absPos);
                    sprite.setColor(Color(255, 255, 255, 255 * currOpacity));
                    sprite.draw(texture);
                }
            }
        }
    }

    MLSprite mainPicture;
    DefaultPictures::Picture sidePicture;
    bool isAnimated;
    clockmy::time_point timeAnimated;
};

//*************************************************************

#endif // BUTTON_HEADER
