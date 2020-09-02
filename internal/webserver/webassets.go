package webserver

import "github.com/leaanthony/wailsv2/v2/internal/assetdb"

var (
	// WebAssets is our single asset db instance.
	// It will be constructed by a dynamically generated method in this directory.
	WebAssets *assetdb.AssetDB = assetdb.NewAssetDB()
)
