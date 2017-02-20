
import qualified App
import qualified Api
import qualified Config
import qualified Data.Text as T
import qualified Database.Persist.Sqlite as P
import qualified Option
import           Network.Wai.Middleware.RequestLogger
import           Network.Wai.Middleware.Static
import           Web.Scotty

main :: IO ()
main = do
    port <- Option.port
    environment <- Option.environment
    database <- Config.get (T.unpack "config/sqlite.yml") environment "Development"
    pool <- P.createSqlitePool database 5

    scotty port $ do
        middleware logStdoutDev
        middleware $ staticPolicy $ addBase "static"

        App.app
        Api.app pool

