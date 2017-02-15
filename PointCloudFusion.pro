TEMPLATE = subdirs

SUBDIRS += \
	PointCloudFusionApp \
	PointCloudFusion
	
PointCloudFusion.depends += PointCloudFusionApp
