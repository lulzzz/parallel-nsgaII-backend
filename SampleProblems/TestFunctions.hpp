//
//  TestFunctions.hpp
//  NSGA-Parallel-Backend
//
//  Created by a1091793 on 26/11/2015.
//
//

#ifndef TestFunctions_h
#define TestFunctions_h

#include <cmath>
#include <tuple>
#include <chrono>
#include <thread>
#include "../Evaluation.hpp"
#include "../ProblemDefinitions.hpp"

class FON : public ObjectivesAndConstraintsBase
{
private:
    
    
    int num_objectives;
    int num_real_decision_vars;
    int num_int_decision_vars;
    int num_constraints;
    double min_dv_value;
    double max_dv_value;

    ProblemDefinitionsSPtr prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints;
    
//    std::vector<double> constraints;
//    std::vector<double> objectives;
//    
    
public:
    FON()
    :   num_objectives(2),
        num_real_decision_vars(2),
        num_int_decision_vars(0),
        num_constraints(0),
        min_dv_value(-4),
        max_dv_value(4),
        prob_defs(new ProblemDefinitions(num_real_decision_vars, min_dv_value, max_dv_value,  num_int_decision_vars, 0, 0, num_objectives, MINIMISATION, num_constraints)),
    objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints))
    {
        
    }
    
    virtual
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::vector<double> & obj = this->objectives_and_constrataints.first;
        
        double sum = 0;
        for (int i = 0; i < num_real_decision_vars; ++i)
        {
            sum -= pow((real_decision_vars[i] - (1.0 / sqrt(3.0))), 2.0);
        }
        obj[0] = 1 - exp(sum);
        sum = 0;
        for (int i = 0; i < num_real_decision_vars; ++i)
        {
            sum -= pow((real_decision_vars[i] + (1.0 / sqrt(3.0))), 2.0);
        }
        obj[1] = 1- exp(sum);
        return (objectives_and_constrataints);
    }
    
    ProblemDefinitionsSPtr & getProblemDefinitions()
    {
        return (prob_defs);
    }
};


class MinMaxFON : public FON
{


public:
    MinMaxFON()
        : FON()
    {
        ProblemDefinitionsSPtr defs = FON::getProblemDefinitions();
        defs->minimise_or_maximise.at(1) = MAXIMISATION;
    }

    virtual
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::pair<std::vector<double>, std::vector<double> > & val = (FON::operator()(real_decision_vars, int_decision_vars));
        val.first.at(1) = -1 * val.first.at(1);
        return (val);
    }

};

class DelayFON : public FON
{
private:
    int delay;
    
public:
    DelayFON(int _delay = 0)
    :   FON(), delay(_delay)
    {
        
    }
    
    virtual
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::this_thread::sleep_for(std::chrono::seconds(delay));
        return (FON::operator()(real_decision_vars, int_decision_vars));
    }
};


class SUM : public ObjectivesAndConstraintsBase
{
private:
    
    int num_objectives;
    int num_real_decision_vars;
    int num_int_decision_vars;
    int num_constraints;
    double min_dv_value;
    double max_dv_value;
    
    ProblemDefinitionsSPtr prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints;
    
    //    std::vector<double> constraints;
    //    std::vector<double> objectives;
    //
    
public:
    SUM()
    :   num_objectives(2),
    num_real_decision_vars(3),
    num_int_decision_vars(0),
    num_constraints(0),
    min_dv_value(1),
    max_dv_value(5),
    prob_defs(new ProblemDefinitions(num_real_decision_vars, min_dv_value, max_dv_value,  num_int_decision_vars, 0, 0, num_objectives, MINIMISATION, num_constraints)),
    objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints))
    {
        
    }
    
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::vector<double> & obj = this->objectives_and_constrataints.first;
        
        double sum = 0;
        for (int i = 0; i < num_real_decision_vars; ++i)
        {
            sum += real_decision_vars[i];
        }
        obj[0] = sum;
        sum = 0;
        for (int i = 0; i < num_real_decision_vars; ++i)
        {
            sum += 1.0 / real_decision_vars[i];
        }
        obj[1] = sum;
        return (objectives_and_constrataints);
    }
    
    ProblemDefinitionsSPtr & getProblemDefinitions()
    {
        return (prob_defs);
    }
};


class IntSum : public ObjectivesAndConstraintsBase
{
private:
    
    int num_objectives;
    int num_real_decision_vars;
    int num_int_decision_vars;
    int num_constraints;
    double min_dv_value;
    double max_dv_value;
    
    ProblemDefinitionsSPtr prob_defs;
    std::pair<std::vector<double>, std::vector<double> > objectives_and_constrataints;
    
    //    std::vector<double> constraints;
    //    std::vector<double> objectives;
    //
    
public:
    IntSum()
    :   num_objectives(2),
    num_real_decision_vars(0),
    num_int_decision_vars(10),
    num_constraints(0),
    min_dv_value(1),
    max_dv_value(5),
    prob_defs(new ProblemDefinitions(num_real_decision_vars, 0, 0,  num_int_decision_vars, min_dv_value, max_dv_value, num_objectives, MINIMISATION, num_constraints)),
    objectives_and_constrataints(std::piecewise_construct, std::make_tuple(num_objectives, std::numeric_limits<double>::max()), std::make_tuple(num_constraints))
    {
        
    }
    
    std::pair<std::vector<double>, std::vector<double> > &
    operator()(const std::vector<double>  & real_decision_vars, const std::vector<int> & int_decision_vars)
    {
        std::vector<double> & obj = this->objectives_and_constrataints.first;
        
        double sum = 0;
        for (int i = 0; i < num_int_decision_vars; ++i)
        {
            sum += int_decision_vars[i];
        }
        obj[0] = sum;
        sum = 0;
        for (int i = 0; i < num_int_decision_vars; ++i)
        {
            sum += 1.0 / (double)int_decision_vars[i];
        }
        obj[1] = sum;
        return (objectives_and_constrataints);
    }
    
    ProblemDefinitionsSPtr & getProblemDefinitions()
    {
        return (prob_defs);
    }
};


#endif /* TestFunctions_h */
