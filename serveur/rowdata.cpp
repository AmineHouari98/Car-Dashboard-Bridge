#include "rowdata.h"



QString rowData::dataToString()
{
    return"chargeMoteur="+QString::number(a_chargeMoteur)
            +"///temp_liquide_froidissement="+QString::number(a_temp_liquide_froidissement)
            +"///regime_moteur="+QString::number(a_regime_moteur)
            +"///vitesse_vehicule="+QString::number(a_vitesse_vehicule)
            +"///temperature_air_admission="+QString::number(a_temperature_air_admission)
            +"///duree_demarrage_moteur="+QString::number(a_duree_demarrage_moteur)
            +"///reservoir="+QString::number(a_reservoir)
            +"///pression_atmospherique="+QString::number(a_pression_atmospherique)
            +"///temp_catalyseur="+QString::number(a_temp_catalyseur)
            +"///temp_air_ambiante="+QString::number(a_temp_air_ambiante)
            +"///position_pedale_accelerateur="+QString::number(a_position_pedale_accelerateur)
            +"///longitude="+QString::number(a_longitude)
            +"///latitude="+QString::number(a_latitude)
            +"///altitude="+QString::number(a_altitude);
}

QStringList rowData::dataToStringList()
{
    QStringList qsl;
    qsl<<QString::number(a_chargeMoteur)
      << QString::number(a_temp_liquide_froidissement)
      << QString::number(a_regime_moteur)
      << QString::number(a_vitesse_vehicule)
      << QString::number(a_temperature_air_admission)
      << QString::number(a_duree_demarrage_moteur)
      << QString::number(a_reservoir)
      << QString::number(a_pression_atmospherique)
      << QString::number(a_temp_catalyseur)
      << QString::number(a_temp_air_ambiante)
      << QString::number(a_position_pedale_accelerateur)
      << QString::number(a_longitude)
      << QString::number(a_latitude)
      << QString::number(a_altitude);
    return qsl;

}









