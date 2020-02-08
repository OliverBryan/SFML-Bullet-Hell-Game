exportedSpawners = {
	"WaveSpawner",
	"HomingSpawner",
	"ShotgunSpawner",
	"GravitySpawner"
}

ec = 0
WaveSpawner = {
	fireTime = 400,
	fill = Color.new(0, 0, 255),
	warningFireFill = Color.new(0, 206, 209),
	spawnEnemies = function(spawner)
		return {
			amount = 1,
			enemies = {
				Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 300, Color.new(0, 0, 0))
			}
		}
	end,
	spawnerUpdate = function(spawner, environment)
		if not spawner.moving then
			return
		end
		if ec > 10 then
			e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 300, Color.new(0, 0, 0))
			environment:addEnemy(e, "WaveSpawner")
			ec = 0
		end
		ec = ec + 1
	end
}

HomingSpawner = {
	fireTime = 400,
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
	enemyUpdate = function(enemy, environment)
		local diffX = enemy.position.x - environment.player.position.x - 10
		local diffY = enemy.position.y - environment.player.position.y - 10
		local distance = math.sqrt(((enemy.position.x - environment.player.position.x) * (enemy.position.x - environment.player.position.x)) + ((enemy.position.y - environment.player.position.y) * (enemy.position.y - environment.player.position.y)))

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