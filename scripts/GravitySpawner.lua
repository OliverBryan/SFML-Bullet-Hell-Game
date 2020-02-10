GravitySpawner = {
	fireTime = 60, --200
	postMoveTime = 20,
	fill = Color.new(128, 128, 128),
	postMoveFill = Color.new(47, 79, 79)
}

GravitySpawner.EnemyInstanceVars = {
	alpha = 194,
	stopped = false,
	grown = false
}

function GravitySpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function GravitySpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x - 6.5, spawner.position.y + 20, 0.0, 2.0, 100000000, Color.new(128, 128, 128, 194))
	e.size.x = 30
	e.size.y = 30
	e:setFatal(false)
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end

function GravitySpawner.enemyUpdate(enemy, environment)
	enemy.instanceVars.alpha = enemy.instanceVars.alpha - 6
	if enemy.instanceVars.alpha < 0 then
		enemy.instanceVars.alpha = 0
	end
	enemy.fill = Color.new(128, 128, 128, enemy.instanceVars.alpha)

	if enemy.instanceVars.stopped then
		enemy.size.x = enemy.size.x + 4
		enemy.size.y = enemy.size.y + 4
		if enemy.size.x >= 100 then
			enemy.size.x = 100
			enemy.size.y = 100
			grown = true
		end
		enemy.position.y = enemy.position.y - enemy.velocity.y
		enemy.instanceVars.alpha = 194
	end

	if floatRectHitTest(environment.player:bounds(), enemy:bounds()) then
		enemy.instanceVars.stopped = true
		enemy.instanceVars.alpha = 194
	else if enemy.size.x > 20 then
		enemy.instanceVars.stopped = false
		enemy.size.x = enemy.size.x - 4
		enemy.size.y = enemy.size.y - 4
		eneny.instanceVars.alpha = 194
		grown = false
	end
end

function GravitySpawner.enemyRender(enemy, window)
	circle = Circle.new(enemy.size.x / 2)
	setCirclePosition(circle, enemy.position.x, enemy.position.y)
	if not enemy.instanceVars.stopped then
		circle:setFill(enemy.fill)
	else
		circle:setFill(Color.new(255, 255, 255))
		circle:setBorder(enemy.fill)
		circle:setBorderWidth(7.0)
	end
	draw(window, circle)
end