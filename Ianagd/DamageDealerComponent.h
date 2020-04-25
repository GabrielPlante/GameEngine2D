#pragma once

namespace ian {
	class DamageDealerComponent
	{
	public:
		unsigned int positionComponentId;

		int damage;

		int range;

		int reloadingTime;//In millisecond

		long long lastShotTime;
	};
}
