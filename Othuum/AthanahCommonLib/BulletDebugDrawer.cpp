#include "BulletDebugDrawer.h"

#include "YolonaOss/Renderer/BoxRenderer.h"

namespace Athanah
{
    void BulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
			YolonaOss::BoxRenderer::drawLine(glm::vec3(from[0], from[1], from[2]), glm::vec3(to[0], to[1], to[2]), 0.02f, glm::vec4(1, 1, 0,1));
    }

    void BulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {

    }

    void BulletDebugDrawer::reportErrorWarning(const char* warningString)                                                                                    {

    }

    void BulletDebugDrawer::draw3dText(const btVector3& location, const char* textString)                                                                    {

    }

    void BulletDebugDrawer::setDebugMode(int debugMode)                                                                                                      {

    }

		int BulletDebugDrawer::getDebugMode() const{
			return DBG_DrawWireframe;
      /*		
			DBG_NoDebug = 0,
		  DBG_DrawWireframe = 1,
		  DBG_DrawAabb = 2,
		  DBG_DrawFeaturesText = 4,
		  DBG_DrawContactPoints = 8,
		  DBG_NoDeactivation = 16,
		  DBG_NoHelpText = 32,
		  DBG_DrawText = 64,
		  DBG_ProfileTimings = 128,
		  DBG_EnableSatComparison = 256,
		  DBG_DisableBulletLCP = 512,
		  DBG_EnableCCD = 1024,
		  DBG_DrawConstraints = (1 << 11),
		  DBG_DrawConstraintLimits = (1 << 12),
		  DBG_FastWireframe = (1 << 13),
		  DBG_DrawNormals = (1 << 14),
		  DBG_DrawFrames = (1 << 15),
		  DBG_MAX_DEBUG_DRAW_MODE			
			*/
    }
}