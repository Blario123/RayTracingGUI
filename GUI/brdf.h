#ifndef BRDF_H
#define BRDF_H

#include <QString>

#include "vec3.h"

class BRDF {
public:
    BRDF(float red, float green, float blue, const QString name = nullptr) : mName(name) {
        mR = red;
        mG = green;
        mB = blue;
    }
    explicit BRDF(Vec3 v, const QString name = nullptr) : mName(name) {
        mR = v.x;
        mG = v.y;
        mB = v.z;
    }
    BRDF &operator=(const BRDF &eq) {
        mR = eq.mR;
        mG = eq.mG;
        mB = eq.mB;
        return *this;
    }
    double r() const {
        return mR;
    }
    double g() const {
        return mG;
    }
    double b() const {
        return mB;
    }
    QString name() const {
        return mName;
    }
private:
    double mR, mG, mB;
    QString mName;
};

#endif //BRDF_H
