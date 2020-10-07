#include "ArtilleryAim.h"
#include <cmath>

namespace Suthanus
{
  glm::vec3 ArtilleryAim::aimSpring(const glm::vec3& targetPositionDifference,float projectileSpeed,bool highTrajectory, float gravity)
  {
    //https://github.com/spring/spring/blob/develop/rts/Sim/Weapons/Cannon.cpp
    //CCannon::CalcWantedDir
		//highTrajectory: there are two solutions. One "direct fire" and one "i am an artillery pew pew" solution. false->direct fire
		//todo: license issue. Outsource this single function to dll, disclose it and sacrifice a child to gpl god (must be fresh)
		
		const float Dsq = (targetPositionDifference.x * targetPositionDifference.x + targetPositionDifference.y * targetPositionDifference.y + targetPositionDifference.z * targetPositionDifference.z);
		const float DFsq = targetPositionDifference.x * targetPositionDifference.x + targetPositionDifference.z * targetPositionDifference.z;
		const float g = gravity;
		const float v = projectileSpeed;
		const float dy = targetPositionDifference.y;
		const float dxz = std::sqrt(DFsq);

		float Vxz = 0.0f;
		float Vy = 0.0f;

		if (Dsq == 0.0f) {
			Vy = highTrajectory ? v : -v;
		}
		else {
			if (Dsq < 1e12f && std::fabs(dy) < 1e6f) {
				const float vsq = v * v;
				const float root1 = vsq * vsq + 2.0f * vsq * g * dy - g * g * DFsq;

				if (root1 >= 0.0f) {
					const float root2 = 2.0f * DFsq * Dsq * (vsq + g * dy + (highTrajectory ? -1.0f : 1.0f) * std::sqrt(root1));

					if (root2 >= 0.0f) {
						Vxz = std::sqrt(root2) / (2.0f * Dsq);
						Vy = (dxz == 0.0f || Vxz == 0.0f) ? v : (Vxz * dy / dxz - dxz * g / (2.0f * Vxz));
					}
				}
			}
		}

		glm::vec3 nextWantedDir(0, 0, 0);

		if (Vxz != 0.0f || Vy != 0.0f) {
			nextWantedDir.x = targetPositionDifference.x;
			nextWantedDir.z = targetPositionDifference.z;
			nextWantedDir = glm::normalize(nextWantedDir);

			nextWantedDir *= Vxz;
			nextWantedDir.y = Vy;
			nextWantedDir = glm::normalize(nextWantedDir);
		}

		return nextWantedDir;
  }
}