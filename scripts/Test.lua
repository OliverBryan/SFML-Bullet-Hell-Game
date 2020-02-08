exportedSpawners = {
	"HomingSpawner",
	"ShotgunSpawner",
	"GravitySpawner"
}

HomingSpawner = {
	fireTime = 60,
	postMoveTime = 10,
	fill = Color.new(0, 128, 0),
	spawnEnemies = function(spawner)
		efill = Color.new(0, 128, 0)
		return {
			amount = 1,
			enemies = {
				Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 0.0, 400, efill)
			}
		}
	end,
	customUpdate = function(enemy, environment)
		local diffX = enemy.position.x - environment.player.position.x - 10
		local diffY = enemy.position.y - environment.player.position.y - 10
		local distance = math.sqrt(((enemy.position.x - environment.player.position.x) ^ 2) + ((enemy.position.y - environment.player.position.x) ^ 2))

		enemy.velocity.x = (-1 / distance) * diffX
		enemy.velocity.y = (-1 / distance) * diffY
	end
}

ShotgunSpawner = {
	fireTime = 30,
	postMoveTime = 30,
	fill = Color.new(128, 0, 128),
	spawnEnemies = function(spawner)
		efill = Color.new(128, 0, 128)
		return {
			amount = 3,
			enemies = {
				Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 3.5, 300, efill),
				Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 1.0, 3.0, 300, efill),
				Enemy.new(spawner.position.x + 3, spawner.position.y + 20, -1.0, 3.0, 300, efill)
			}
		}
	end
}

--[[
ShotgunSpawner = SpawnerBase:new(30, 20, Color.new(128, 0, 128), Color.new(128, 0, 128))

function ShotgunSpawner:spawnEnemy(spawner) {

}
--]]