#pragma once

namespace C2DCore
{
	class IRenderPart
	{
	public:
		virtual ~IRenderPart() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void OnDestroy() const = 0;
	};
}
