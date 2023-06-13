#pragma once
#include "c2dpch.h"

#define BIND_ACTION_FN(method) std::bind(&method, *this, std::placeholders::_1)
#define BIND_ACTION_FN_PM(method, parameter_count) std::bind(&method, this, std::_Ph<parameter_count>{})
#define BIND_LAMBDA_FN_PM(lambda, parameter_count) std::bind(&method, std::_Ph<parameter_count>{})

namespace C2DCore::EventSystem
{
	template<typename... Args>
	class Action
	{
	public:
		Action() = default;
		~Action() = default;

		void Invoke(Args... args)
		{
			for (auto& callback : m_Callbacks)
			{
				callback(args...);
			}
		}

		void operator()(Args... args)
		{
			Invoke(args...);
		}

		void operator+=(const std::function<void(Args...)> callback)
		{
			m_Callbacks.push_back(callback);
		}

		void operator-=(const std::function<void(Args...)> callback)
		{
			auto it = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const auto& func)
				{
					return func.target<void(Args...)>() == callback.target<void(Args...)>();
				});

			if (it != m_Callbacks.end())
			{
				m_Callbacks.erase(it);
			}
		}

	private:
		std::vector<std::function<void(Args...)>> m_Callbacks;
	};
}
