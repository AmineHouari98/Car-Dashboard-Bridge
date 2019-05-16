#ifndef ROWDATA_H
#define ROWDATA_H


#include <QGeoCoordinate>
#include "PropertyHelper.h"


class rowData: public QObject
{
private:
    Q_OBJECT
public:
    QString dataToString();
    QStringList dataToStringList();

    AUTO_PROPERTY(int,chargeMoteur)
//    Q_PROPERTY(int chargeMoteur READ chargeMoteur WRITE chargeMoteur NOTIFY chargeMoteur_Changed )
//    public:
//       int chargeMoteur() const { return a_chargeMoteur ; }
//    Q_SIGNAL void chargeMoteur_Changed(int value);
//       void chargeMoteur(int value) {
//          if (a_chargeMoteur == value)  return;
//          a_chargeMoteur = value;
//          emit chargeMoteur_Changed(value);
//        }
//    private:
//       int a_chargeMoteur;
    AUTO_PROPERTY(int,temp_liquide_froidissement)
    AUTO_PROPERTY(int,regime_moteur)
    AUTO_PROPERTY(int,vitesse_vehicule)
    AUTO_PROPERTY(int,temperature_air_admission)
    AUTO_PROPERTY(int,duree_demarrage_moteur)
    AUTO_PROPERTY(int,reservoir)
    AUTO_PROPERTY(int,pression_atmospherique)
    AUTO_PROPERTY(int,temp_catalyseur)
    AUTO_PROPERTY(int,temp_air_ambiante)
    AUTO_PROPERTY(int,position_pedale_accelerateur)
    //...
    AUTO_PROPERTY(float,longitude)
    AUTO_PROPERTY(float,latitude)
    AUTO_PROPERTY(float,altitude)
    AUTO_PROPERTY(QGeoCoordinate,coordinate)



};
//Q_DECLARE_METATYPE(rowData)
#endif // ROWDATA_H
