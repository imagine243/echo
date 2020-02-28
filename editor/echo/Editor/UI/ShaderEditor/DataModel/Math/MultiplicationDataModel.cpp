#include "MultiplicationDataModel.h"
#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include "DataFloat.h"
#include "DataVector2.h"
#include "DataVector3.h"
#include "DataVector4.h"
#include "DataInvalid.h"
#include "ShaderScene.h"

namespace DataFlowProgramming
{
    MultiplicationDataModel::MultiplicationDataModel()
    {
        m_inputDataTypes = 
        {
            {"any", "A"},
            {"any", "B"},
        };

        m_inputs.resize(m_inputDataTypes.size());

        m_outputs.resize(1);
        m_outputs[0] = std::make_shared<DataInvalid>(this);
        m_outputs[0]->setVariableName(getVariableName());
    }

    QJsonObject MultiplicationDataModel::save() const
    {
        QJsonObject modelJson = NodeDataModel::save();
        return modelJson;
    }

    void MultiplicationDataModel::restore(QJsonObject const &p)
    {
    }

    unsigned int MultiplicationDataModel::nPorts(PortType portType) const
    {
        unsigned int result = 1;

        switch (portType)
        {
            case PortType::In: result = m_inputs.size(); break;
            case PortType::Out:result = m_outputs.size(); break;
            default:                       break;
        }

        return result;
    }

    NodeDataType MultiplicationDataModel::dataType(PortType portType, PortIndex portIndex) const
    {
        if(portType==PortType::In)
        {
            return m_inputDataTypes[portIndex];
        }
        else if (portType == PortType::Out)
        {
            return m_outputs[portIndex]->type();
        }
        
        return NodeDataType {"unknown", "Unknown"};
    }

    std::shared_ptr<NodeData> MultiplicationDataModel::outData(PortIndex portIndex)
    {
        return m_outputs[portIndex];
    }

    void MultiplicationDataModel::setInData(std::shared_ptr<NodeData> nodeData, PortIndex port)
    {
        m_inputs[port] = std::dynamic_pointer_cast<DataAny>(nodeData);
        if (m_inputs[0] && m_inputs[1])
        {
            if (m_inputs[0]->getInternalData()->type().id == "float" && m_inputs[1]->getInternalData()->type().id == "float")
            {
				m_outputs[0] = std::make_shared<DataFloat>(this, "float");
				m_outputs[0]->setVariableName(getVariableName());
            }
        }
        else
        {
			m_outputs[0] = std::make_shared<DataInvalid>(this);
			m_outputs[0]->setVariableName(getVariableName());
        }
    }

    bool MultiplicationDataModel::generateCode(ShaderCompiler& compiler)
    {
        if (m_inputs[0] && m_inputs[1])
        {
            compiler.addCode(Echo::StringUtil::Format("\t%s %s = %s * %s;\n",
                m_outputs[0]->type().id.c_str(),
                m_outputs[0]->getVariableName().c_str(),
                m_inputs[0]->getInternalData()->getVariableName().c_str(),
                m_inputs[1]->getInternalData()->getVariableName().c_str()));
        }

        return true;
    }
}
