#pragma once

struct progress
{
	double all;
	double done;

	double percent() const { return done / all * 100; }
};