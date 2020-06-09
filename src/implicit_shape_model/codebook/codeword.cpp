/*
 * BSD 3-Clause License
 *
 * Full text: https://opensource.org/licenses/BSD-3-Clause
 *
 * Copyright (c) 2018, Viktor Seib
 * All rights reserved.
 *
 */

#include "codeword.h"
#include "codeword_factory.h"

namespace ism3d
{
    int Codeword::m_maxId = 0;

    Codeword::Codeword(const std::vector<float>& data, int numFeatures, float weight)
    {
        m_data = std::vector<float>(data);
        m_numFeatures = numFeatures;
        m_weight = weight;

        m_id = m_maxId;
        m_maxId++;
    }

    Codeword::Codeword()
    {
        m_id = m_maxId;
        m_numFeatures = 0;
        m_weight = 1.0f;
        m_maxId++;
    }

    Codeword::~Codeword()
    {
    }

    void Codeword::setData(const std::vector<float>& data, int numFeatures, float weight)
    {
        m_data = std::vector<float>(data);
        m_numFeatures = numFeatures;
        m_weight = weight;
    }

    const std::vector<float>& Codeword::getData() const
    {
        return m_data;
    }

    int Codeword::getId() const
    {
        return m_id;
    }

    int Codeword::getNumFeatures() const
    {
        return m_numFeatures;
    }

    float Codeword::getWeight() const
    {
        return m_weight;
    }

    void Codeword::addFeature(unsigned classId, unsigned instanceId)
    {
        m_feature_classes.push_back(classId);
        m_feature_instances.push_back(instanceId);
    }

    const std::vector<unsigned>& Codeword::getFeatureClasses() const
    {
        return m_feature_classes;
    }

    void Codeword::iSaveData(boost::archive::binary_oarchive &oa) const
    {
        oa << m_id;
        oa << m_numFeatures;
        oa << m_weight;

        m_maxId = m_id + 1; // TODO VS: remove this

        oa << m_feature_classes;
        oa << m_feature_instances;
        oa << m_data;
    }

    bool Codeword::iLoadData(boost::archive::binary_iarchive &ia)
    {
        ia >> m_id;
        ia >> m_numFeatures;
        ia >> m_weight;
        ia >> m_feature_classes;
        ia >> m_feature_instances;
        ia >> m_data;

        return true;
    }
}
