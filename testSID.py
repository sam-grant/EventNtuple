import DataProducts
import GeneralUtilities
import MCDataProducts

# GID --> A test should return cosmicCORSIKA
gid = MCDataProducts.GenId()
pname=gid.name(44) #cosmicCorsika (test)
print("testing GID", pname)

# SID
sid = DataProducts.SurfaceId() # surafaceID object
ids = sid.id() #EnumToStringSparse<SurfaceIdDetail>
print( ids)

name = ids.typeName()
print(name)
