#include "anim_property.h"
#include "engine/core/log/Log.h"
#include "engine/core/scene/node.h"

namespace Echo
{
	AnimProperty* AnimProperty::create(AnimProperty::Type type)
	{
		switch (type)
		{
		case AnimProperty::Type::Bool:			return EchoNew(AnimPropertyBool);
		case AnimProperty::Type::Float:			return EchoNew(AnimPropertyFloat);
		case AnimProperty::Type::Vector3:		return EchoNew(AnimPropertyVec3);
		case AnimProperty::Type::Vector4:		return EchoNew(AnimPropertyVec4);
		case AnimProperty::Type::Quaternion:	return EchoNew(AnimPropertyQuat);
		case AnimProperty::Type::String:		return EchoNew(AnimPropertyString);
		case AnimProperty::Type::Object:		return EchoNew(AnimPropertyObject);
		default:								return nullptr;
		}

		return nullptr;
	}

	void AnimProperty::setInterpolationType(AnimCurve::InterpolationType type)
	{ 
		m_interpolationType = type;
	}

	AnimPropertyCurve::AnimPropertyCurve(AnimProperty::Type type, i32 curveCount)
		: AnimProperty(type)
	{
		m_curves.reserve(curveCount);
		for (i32 i = 0; i < curveCount; i++)
		{
			m_curves.emplace_back(EchoNew(AnimCurve));
		}
	}
    
    AnimPropertyCurve::~AnimPropertyCurve()
    {
        EchoSafeDeleteContainer(m_curves, AnimCurve);
    }

	void AnimPropertyCurve::setInterpolationType(AnimCurve::InterpolationType type)
	{
		AnimProperty::setInterpolationType(type);
		for (AnimCurve* curve : m_curves)
		{
			curve->setType(type);
		}
	}

	void AnimPropertyCurve::optimize()
	{
		for (AnimCurve* curve : m_curves)
		{
			curve->optimize();
		}
	}

	ui32 AnimPropertyCurve::getLength()
	{
		ui32 length = 0;
		for (AnimCurve* curve : m_curves)
		{
			if (curve->getLength() > length)
				length = curve->getLength();
		}

		return length;
	}

	void AnimPropertyCurve::setKeyValue(int curveIdx, int keyIdx, float value)
	{
		m_curves[curveIdx]->setValueByKeyIdx(keyIdx, value);
	}

	void AnimPropertyCurve::addKeyToCurve(int curveIdx, ui32 time, float value)
	{
		m_curves[curveIdx]->addKey(time, value);
	}

	AnimPropertyFloat::AnimPropertyFloat()
		: AnimPropertyCurve(Type::Float, 1)
	{}

	void AnimPropertyFloat::addKey(ui32 time, float value)
	{
		for (size_t i = 0; i < m_curves.size(); i++)
			m_curves[i]->addKey(time, value);
	}

	void AnimPropertyFloat::updateToTime(ui32 time, ui32 deltaTime)
	{
		for (size_t i = 0; i < m_curves.size(); i++)
			m_value = m_curves[i]->getValue(time);
	}

	AnimPropertyVec3::AnimPropertyVec3()
		: AnimPropertyCurve(Type::Vector3, 3)
	{}

	void AnimPropertyVec3::addKey(ui32 time, const Vector3& value)
	{
		for (int i = 0; i < int(m_curves.size()); i++)
			m_curves[i]->addKey(time, value[i]);
	}

	void AnimPropertyVec3::updateToTime(ui32 time, ui32 deltaTime)
	{
		for (int i = 0; i < int(m_curves.size()); i++)
			m_value[i] = m_curves[i]->getValue(time);
	}

	AnimPropertyVec4::AnimPropertyVec4() 
		: AnimPropertyCurve(Type::Vector4, 4)
	{}

	void AnimPropertyVec4::addKey(ui32 time, const Vector4& value)
	{
		for (int i = 0; i < int(m_curves.size()); i++)
			m_curves[i]->addKey(time, value[i]);
	}

	void AnimPropertyVec4::updateToTime(ui32 time, ui32 deltaTime)
	{
		for (int i = 0; i < int(m_curves.size()); i++)
			m_value[i] = m_curves[i]->getValue(time);
	}

	void AnimPropertyBool::addKey(ui32 time, bool value)
	{
		m_keys[time] = value;
	}

	void AnimPropertyBool::updateToTime(ui32 time, ui32 deltaTime)
	{
		if (deltaTime)
		{
			m_isActive = false;

			for (auto it : m_keys)
			{
				ui32 preTime = time - deltaTime;
				if (it.first >= preTime && it.first <= time)
				{
					m_value = it.second;
					m_isActive = true;
					break;
				}
			}
		}
	}

	ui32 AnimPropertyBool::getLength()
	{
		return getEndTime() - getStartTime();
	}

	ui32 AnimPropertyBool::getStartTime()
	{
		return m_keys.size() ? m_keys.begin()->first : 0;
	}

	ui32 AnimPropertyBool::getEndTime()
	{
		return m_keys.size() ? m_keys.rbegin()->first : 0;
	}

	void AnimPropertyQuat::addKey(ui32 time, const Quaternion& value)
	{
		m_keys.emplace_back(time, value);
	}

	ui32 AnimPropertyQuat::getLength()
	{
		return m_keys.size() ? m_keys.back().m_time : 0;
	}

	void AnimPropertyQuat::updateToTime(ui32 time, ui32 deltaTime)
	{
		if (m_keys.empty())
		{
			m_vlaue = Quaternion::IDENTITY;
		}
		else if (m_keys.size() == 1)
		{
			m_vlaue = m_keys[0].m_value;
		}
		else
		{
			// get base key and next key
			i32 curKey = 0;
			i32 keyTotal = i32(m_keys.size()) - 1;
			for (i32 i = 0; i < keyTotal; i++)
			{
				if (time > m_keys[i].m_time && time < m_keys[i + 1].m_time)
					curKey = i;
			}

			// calculate value
			const Key& pre = m_keys[curKey];
			const Key& next = m_keys[curKey + 1];
			float ratio = Math::Clamp(float(time - pre.m_time) / float(next.m_time - pre.m_time), 0.f, 1.f);
			Quaternion::Slerp(m_vlaue, pre.m_value, next.m_value, ratio, true);
		}
	}

	ui32 AnimPropertyObject::getLength()
	{
		return 0;
	}

	void AnimPropertyObject::updateToTime(ui32 time, ui32 deltaTime)
	{

	}

	void AnimPropertyString::addKey(ui32 time, const String& value)
	{
		m_keys[time] = value;
	}

	void AnimPropertyString::updateToTime(ui32 time, ui32 deltaTime)
	{
		if (deltaTime)
		{
			m_isActive = false;

			for (auto it : m_keys)
			{
				ui32 preTime = time - deltaTime;
				if (it.first >= preTime && it.first <= time)
				{
					m_value = it.second;
					m_isActive = true;
					break;
				}
			}
		}
	}

	ui32 AnimPropertyString::getLength()
	{
		return getEndTime() - getStartTime();
	}

	ui32 AnimPropertyString::getStartTime()
	{
		return m_keys.size() ? m_keys.begin()->first : 0;
	}

	ui32 AnimPropertyString::getEndTime()
	{
		return m_keys.size() ? m_keys.rbegin()->first : 0;
	}
}
