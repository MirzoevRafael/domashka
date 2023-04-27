using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySqlConnector;

namespace Ball
{
    public class Database
    {
        private MySqlConnection? _connection = new MySqlConnection("Server=localhost;port=3306;" +
            "database=scorelist;User ID=root;password=");
        public MySqlConnection? Connection { get { return _connection; } }
        private string _tableName;
        public Database() 
        {
            _connection.Open();
            _tableName = "`rating" + DateTime.Now.ToString() + "`";
            var cmd = _connection?.CreateCommand();
            cmd.CommandText = $"CREATE TABLE `scorelist`.{_tableName} " +
                $"(`Id` SERIAL NOT NULL , `Color` VARCHAR(64) NOT NULL , `Score` INT NOT NULL DEFAULT '0' , PRIMARY KEY (`Id`));";
            cmd.ExecuteNonQuery();
        }

        public void NewSquare(Square s)
        {
            var cmd = _connection?.CreateCommand();
            cmd.CommandText = $"INSERT INTO {_tableName} (Color) VALUES (\"{s.COLOR}\");";
            cmd.ExecuteNonQuery();
        }
        public void NewScore(Square s)
        {
            var cmd = _connection?.CreateCommand();
            cmd.CommandText = $"UPDATE {_tableName} SET Score = {s.Score} WHERE Id = {s.Id};";
            cmd.ExecuteNonQuery();
        }
    }
}
