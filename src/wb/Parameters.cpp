#include <iostream>
#include <fstream>

#include <yaml-cpp/yaml.h>

#include "Parameters.h"

using std::cout;
using std::endl;

Parameters::Parameters()
{
     history_length = 10;
     history_distance = 15;
     ratio_threshold = 0.00162001;     
     static_threshold = 150;
     gradient_threshold = 150;
     
     threshold_type = ratio_type;     

     min_velocity_threshold = 15;
     max_velocity_threshold = 18;

     covar_threshold = 30;
     max_leg_diff = 10000;
     min_velocity_threshold_2 = 5;

     class_age_confirmed = 5;

     min_relative_norm = 20;
}

void Parameters::set_yaml_file(std::string yaml_file)
{
     yaml_file_ = yaml_file;
     
     if (yaml_file_ != "") {
          std::ifstream fin(yaml_file_.c_str());
          YAML::Parser parser(fin);     
          YAML::Node doc;
          parser.GetNextDocument(doc);
          
          if(const YAML::Node *p = doc.FindValue("ratio_threshold")) {
               *p >> ratio_threshold;
          }

          if(const YAML::Node *p = doc.FindValue("static_threshold")) {
               *p >> static_threshold;
          }

          if(const YAML::Node *p = doc.FindValue("gradient_threshold")) {
               *p >> gradient_threshold;
          }

          if(const YAML::Node *p = doc.FindValue("history_length")) {
               *p >> history_length;
          }
          
          if(const YAML::Node *p = doc.FindValue("history_distance")) {
               *p >> history_distance;
          }
          
          if(const YAML::Node *p = doc.FindValue("min_velocity_threshold")) {
               *p >> min_velocity_threshold;
          }
          
          if(const YAML::Node *p = doc.FindValue("max_velocity_threshold")) {
               *p >> max_velocity_threshold;
          }

          if(const YAML::Node *p = doc.FindValue("covar_threshold")) {
               *p >> covar_threshold;
          }

          if(const YAML::Node *p = doc.FindValue("max_leg_diff")) {
               *p >> max_leg_diff;
          }

          if(const YAML::Node *p = doc.FindValue("min_velocity_threshold_2")) {
               *p >> min_velocity_threshold_2;
          }

          if(const YAML::Node *p = doc.FindValue("class_age_confirmed")) {
               *p >> class_age_confirmed;
          }

          if(const YAML::Node *p = doc.FindValue("min_relative_norm")) {
               *p >> min_relative_norm;
          }

          if(const YAML::Node *p = doc.FindValue("threshold_type")) {
               int type;
               *p >> type;

               switch ((ThresholdType_t)type) {
               case static_type:
                    threshold_type = static_type;
                    break;
               case ratio_type:
                    threshold_type = ratio_type;
                    break;
               case gradient_type:
                    threshold_type = gradient_type;
                    break;
               default:                    
                    cout << "ERROR: Invalid threshold_type: " << type << endl;
                    break;
               }
          }
     }
}
